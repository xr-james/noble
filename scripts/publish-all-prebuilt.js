
'use strict';

const spawn = require('child_process').spawn;

/*
 * This script builds and publishes precompiled binaries for pc-ble-driver-js
 * to GitHub. Using the platform and arch for the current system, and building
 * binaries for all the runtime/version combinations configured below.
 */

const BUILD_CONFIGS = [
    {
        npm_config_runtime: 'node',
        npm_config_target: '12.18.3',
    },
    {
        npm_config_runtime: 'node',
        npm_config_target: '14.16.0',
    },
];

function runNpm(args, envVars) {
    return new Promise((resolve, reject) => {
        const env = Object.assign({}, process.env);
        Object.keys(envVars).forEach(key => {
            env[key] = envVars[key];
        });
        const options = {
            env,
            shell: true,
            stdio: 'inherit',
        };
        spawn('npm', args, options).on('exit', code => {
            if (code === 0) {
                resolve();
            } else {
                reject(new Error(`The npm process exited with code ${code}`));
            }
        });
    });
}

function cleanPrebuilt(config) {
    console.log('Removing any locally existing .node binaries');
    return runNpm(['run', 'clean-prebuilt'], config);
}

function prebuild(config) {
    console.log(`Building ${JSON.stringify(config)}`);
    return runNpm(['install'], config);
}

function packagePrebuilt(config) {
    console.log(`Packaging ${JSON.stringify(config)}`);
    return runNpm(['run', 'package-prebuilt'], config);
}

function publishPrebuilt(config) {
    console.log(`Publishing ${JSON.stringify(config)}`);
    return runNpm(['run', 'publish-prebuilt'], config);
}

function buildAndPublishAll(configs) {
    return configs.reduce((prev, config) => (
        prev.then(() => cleanPrebuilt(config))
            .then(() => prebuild(config))
            .then(() => packagePrebuilt(config))
            .then(() => publishPrebuilt(config))
    ), Promise.resolve());
}

if (!process.env.NODE_PRE_GYP_GITHUB_TOKEN) {
    console.error('Environment variable NODE_PRE_GYP_GITHUB_TOKEN was not provided. ' +
        'Unable to publish to GitHub.');
    process.exit(1);
}

buildAndPublishAll(BUILD_CONFIGS)
    .catch(error => {
        console.error(`Error when building/publishing binaries: ${error.message}.`);
        process.exit(1);
    });

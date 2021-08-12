/* eslint-disable space-before-function-paren */
/* eslint-disable comma-dangle */
/* eslint-disable indent */

'use strict';

const spawn = require('child_process').spawn;
const os = require('os');

const platform = os.platform();
if (platform === 'win32') {
    console.log(`Building win`);
    // runNpm(['run', 'build-win']);
} else {
    console.log(`Building...`);
    runNpm(['run', 'build']);
}

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

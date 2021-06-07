const os = require('os');

module.exports = function (options) {
  const platform = os.platform();

  if (process.env.NOBLE_WEBSOCKET) {
    return new (require('./websocket/bindings'))(options);
  } else if (process.env.NOBLE_DISTRIBUTED) {
    return new (require('./distributed/bindings'))(options);
  } else if (platform === 'darwin') {
    return new (require('./mac/bindings'))(options);
  } else if (platform === 'linux' || platform === 'freebsd') {
    return new (require('./hci-socket/bindings'))(options);
  } else if (platform === 'win32') {
    const ver = os.release().split('.').map(Number);
    if (!(ver[0] > 10 ||
      (ver[0] === 10 && ver[1] > 0) ||
      (ver[0] === 10 && ver[1] === 0 && ver[2] >= 15063))) {
      return new (require('./hci-socket/bindings'))(options);
    }
    //noble-winrt for Windows 10 build 10.0.15063 or later
    return new (require('./winrt/bindings'))(options);
    
  } else {
    throw new Error('Unsupported platform');
  }
};

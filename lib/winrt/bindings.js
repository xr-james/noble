const events = require('events');
const util = require('util');

const NobleWinrt = require('bindings')('noble_winrt').NobleWinrt;
// console.log(NobleWinrt);

util.inherits(NobleWinrt, events.EventEmitter);

module.exports = NobleWinrt;

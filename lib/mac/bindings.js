const events = require('events');
const util = require('util');

const NobleMac = require('bindings')('noble_mac').NobleMac;

util.inherits(NobleMac, events.EventEmitter);

module.exports = NobleMac;

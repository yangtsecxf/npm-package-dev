process.chdir('.\\node_modules\\engine-cxf');

var engine = require("engine-cxf");
console.log(engine.echo("下面是随机数:"));

console.log(engine.random(0, 0));
console.log(engine.random(1, 1));
console.log(engine.random(1, 10));
console.log(engine.random(1, 100));
console.log(engine.random(0, 1000));

console.log(engine.random(0, 10000));
console.log(engine.random(0, 100000));
console.log(engine.random(0, 1000000));

console.log(engine.random(0, 10000000));
console.log(engine.random(0, 100000000));
console.log(engine.random(0, 1000000000));

console.log(engine.random(0, 10000000000));


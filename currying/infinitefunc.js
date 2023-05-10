// Achive this function : sum(1)(2)(3)(4)....()

function sum(x) {
  return function (...args) {
    if (args.length === 0) {
      return x;
    }
    return sum(x + args[0]);
  };
}

console.log(sum(1)());
console.log(sum(1)(2)());
console.log(sum(1)(2)(3)());
console.log(sum(1)(2)(3)(4)());

// Implement the Bind polyfill
// Polyfill:- A custom implementation of a function which acts as browser fallback when the function is not natively supported.

// bind method
let obj = {
  name: "arnab",
  place: "bangalore",
};

function func(from, age) {
  console.log(
    this.name +
      " lives in " +
      this.place +
      " and is from " +
      from +
      " aged " +
      age
  );
}

let funcCopy = func.bind(obj, "kolkata");
funcCopy(25);

// polyfill for bind

Function.prototype.myBind = function (...arg) {
  let obj = this;
  let args1 = arg.slice(1);
  return function (...args2) {
    obj.apply(arg[0], [...args1, ...args2]);
  };
};

let funcCopy1 = func.myBind(obj, "kolkata"); //myBind is bind polyfill
funcCopy1(25);

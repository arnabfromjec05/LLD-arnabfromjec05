/**
 * Everything entity like Function, Array etc derived from object
 * Means - All entity's prototype are derived from Object.prototype at some level
 */

// now newFunc will be available to all Function objects
Function.prototype.newFunc = () => {
  console.log("New function added to function prototype");
};

// now newProp will be available to all Array objects
Array.prototype.newProp = "New property";

// now universalProp will be available to all Objects
Object.prototype.universalProp = "hello world!";

//test --->

let func = function () {
  console.log("Dummy function");
};
func.newFunc();

let arr = [1, 2, 3];
console.log(arr.newProp);

console.log(arr.universalProp, func.universalProp);

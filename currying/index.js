// function currying

// using bind method

function multiply(x, y) {
  console.log(x * y);
}

const multiplyByTwo = multiply.bind(this, 2);
const multiplyByThree = multiply.bind(this, 3);

multiplyByTwo(4);
multiplyByThree(4);

// using closures

function add(x) {
  return function (y) {
    console.log(x + y);
  };
}

const addWithTwo = add(2);
const addWithThree = add(3);

addWithTwo(4);
addWithThree(4);

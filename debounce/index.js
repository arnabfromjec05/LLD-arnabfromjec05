// debounce functionality ------

let counter = 0;
const getData = () => {
  // call some api here
  console.log("API called", counter++);
};

const debounce = function (fn, delay) {
  let timer;
  return function () {
    clearTimeout(timer);
    timer = setTimeout(() => {
      fn.apply(this);
    }, delay);
  };
};

const getDataDebounced = debounce(getData, 500);

// throttle functionality -------

const throttle = function (fn, delay) {
  let flag = true;
  return function () {
    if (flag) {
      fn();
      flag = false;
      setTimeout(() => {
        flag = true;
      }, delay);
    }
  };
};

const getDataThrottled = throttle(getData, 2000); //throttle api calls for 2sec

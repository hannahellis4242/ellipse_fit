import { readDataFile } from "./read";

readDataFile("data.txt").then((value) => {
  console.log(value);
});

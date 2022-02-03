import { createReadStream } from "fs";
import csvParser from "csv-parser";

interface RawData {
  x: string;
  y: string;
}

export type DataPoint = [number, number];

const process = (xs: RawData[]): DataPoint[] => {
  return xs.map(({ x, y }) => [Number(x), Number(y)]);
};

export const readDataFile = async (filename: string): Promise<DataPoint[]> => {
  return new Promise((resolve) => {
    const results: RawData[] = [];
    createReadStream(filename)
      .pipe(csvParser())
      .on("data", (data) => results.push(data))
      .on("end", () => {
        //process into an array
        const dataPoints = process(results);
        resolve(dataPoints);
      });
  });
};

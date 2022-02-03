import Point from "./Point";

export default class Translate {
  private x: number;
  private y: number;
  constructor([x, y]: Point) {
    this.x = x;
    this.y = y;
  }
  exec([x, y]: Point): Point {
    return [x + this.x, y + this.y];
  }
}

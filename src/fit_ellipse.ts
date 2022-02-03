import Ellipse from "./Ellipse";
import Point from "./Point";
import Translate from "./Translate";

class Rotation {
  private s: number;
  private c: number;
  constructor(angle: number) {
    const angle_rad = (angle * Math.PI) / 180.0;
    this.s = Math.sin(angle_rad);
    this.c = Math.cos(angle_rad);
  }
  exec([x, y]: [number, number]): [number, number] {
    return [x * this.c - y * this.s, x * this.s + y * this.c];
  }
}

class Stretch {}

const transform_points = (e: Ellipse, data: Point[]): Point[] => {
  //step 1 translate
  const translation = new Translate([-e.offset.x, -e.offset.y]);
  //step 2 rotate data
  const rotation = new Rotation(e.angle);
  //step 3 stretch

  return data
    .map((value) => translation.exec(value))
    .map((value) => rotation.exec(value));
};

export const fitness = (e: Ellipse, data: [number, number][]): number => {
  /*This function determines how well the given ellipse fits the current data.
    It does this by assuming the data already fits the given ellipse and performing
    transformations to bring the ellipse to the unit circle. It then looks at the
    difference in the radius of the transformed points compared to the expected 
    unit circle.

    It returns that difference so that 0 would mean a perfect fit, and any number
    greater than that would be a worse fit. */
};

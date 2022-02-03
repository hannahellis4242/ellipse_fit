import Point from "../src/Point";
import Translate from "../src/Translate";
describe("Translate", () => {
  it("zero zero offset does not lead to translation", () => {
    const offset: Point = [0, 0];
    const translation = new Translate(offset);
    const point: Point = [5, 2];
    expect(translation.exec(point)).toEqual(point);
  });
  it("translating origin should move to offset", () => {
    const offset: Point = [2, 5];
    const translation = new Translate(offset);
    const point: Point = [0, 0];
    expect(translation.exec(point)).toEqual(offset);
  });
});

export class Offset {
  constructor(public x: number, public y: number) {}
}

export default class Ellipse {
  constructor(
    public major: number,
    public minor: number,
    public offset: Offset,
    public angle: number
  ) {}
}

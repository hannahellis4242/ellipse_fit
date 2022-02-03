export default class Option<T> {
  constructor(public data: T | undefined) {}
  public static Some<T>(x: T): Option<T> {
    return new Option<T>(x);
  }
  public static None<T>(): Option<T> {
    return new Option<T>(undefined);
  }

  unwrap(): T {
    if (this.data) {
      return this.data;
    }
    throw new Error("called `Option::unwrap()` on a `None` value");
  }

  unwrap_or(x: T): T {
    return this.data ? this.data : x;
  }

  map<U>(fn: (x: T) => U): Option<U> {
    return this.data ? new Option(fn(this.data)) : new Option<U>(undefined);
  }

  and_then<U>(fn: (x: T) => Option<U>): Option<U> {
    return this.data ? fn(this.data) : new Option<U>(undefined);
  }
}

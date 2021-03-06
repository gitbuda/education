// https://fasterthanli.me/articles/a-half-hour-to-learn-rust

use std::convert::TryInto;

fn dummy_print<T: std::fmt::Display + std::fmt::Debug>(x: T) -> i32 {
    // Display print.
    println!("{}", x);
    // Debug print.
    // println!("{:?}", x);
    0
}

fn print_type_name<T>(_val: &T) {
    println!("{}", std::any::type_name::<T>());
}

fn flip(x: bool) -> bool {
    match x {
        true => false,
        false => true
    }
}

struct DummyVec {
    x: f64,
    y: f64,
}

#[derive(Clone, Copy, Debug)]
struct Number {
    odd: bool,
    value: i32,
}

impl std::fmt::Display for Number {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        write!(f, "({}, {})", self.odd, self.value)
    }
}

impl Number {
    fn is_strictly_positive(self) -> bool {
        self.value > 0
    }
}

trait Signed {
    fn is_strictly_negative(self) -> bool;
}

impl Signed for Number {
    fn is_strictly_negative(self) -> bool {
        self.value < 0
    }
}

impl std::ops::Neg for Number {
    // Self means that type (Number).
    type Output = Self;
    fn neg(self) -> Self {
        Number {
            value: -self.value,
            odd: self.odd,
        }
    }
}

// impl std::clone::Clone for Number {
//     fn clone(&self) -> Self {
//         Self { ..*self }
//     }
// }
// impl std::marker::Copy for Number {}

#[derive(Debug)]
struct NonCopyNumber {
    odd: bool,
    value: i32,
}

impl std::fmt::Display for NonCopyNumber {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        write!(f, "({}, {})", self.odd, self.value)
    }
}

struct Pair<T> {
    a: T,
    b: T,
}

fn print_number(n: Number) {
    match n {
        Number { odd: true, value } => println!("Odd number: {}", value),
        Number { odd: false, value } => println!("Even number: {}", value),
    }
}

fn print_number_ref(n: &Number) {
    // if let Number { odd: true, value } = n {
    //     println!("Odd number: {}", value);
    // } else if let Number { odd: false, value } = n {
    //     println!("Even number: {}", value);
    // }
    match n {
        Number { odd: true, value } => println!("Odd number: {}", value),
        Number { odd: false, value } => println!("Even number: {}", value),
    }
    // match n {
    //     Number { value: 1, .. } => println!("One"),
    //     Number { value: 2, .. } => println!("Two"),
    //     Number { value, .. } => println!("{}", value),
    //     // if that last arm didn't exist, we would get a compile-time error
    // }
}

fn invert(n: &mut Number) {
    n.value = -n.value;
}

// 'a is a lifetime argument.
// For the lifetime stuff you need an additional template parameter.
struct NumRef<'a, T> {
    x: &'a T,
}

fn as_num_ref<'a, T>(x: &'a T) -> NumRef<'a, T> {
    NumRef { x: &x }
}

fn number_value<'lifetime>(num1: &'lifetime NonCopyNumber, num2: &NonCopyNumber) -> &'lifetime i32 {
    &num1.value
}

#[derive(Debug)]
struct RefStrPerson<'a> {
    name: &'a str,
}
impl std::fmt::Display for RefStrPerson<'_> {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        write!(f, "Person (name: {})", self.name)
    }
}

#[derive(Debug)]
struct Person {
    name: String,
}
impl std::fmt::Display for Person {
    fn fmt(&self, f: &mut std::fmt::Formatter<'_>) -> std::fmt::Result {
        write!(f, "Person (name: {})", self.name)
    }
}

fn hardcoded_utf8_example() -> Result<&'static str, std::str::Utf8Error> {
    match std::str::from_utf8(&[240, 159, 141, 137]) {
    // match std::str::from_utf8(&[195, 40]) {
        Ok(s) => return Ok(s),
        Err(e) => return Err(e),
    }
}
fn hardcoded_utf8_example_short() -> Result<&'static str, std::str::Utf8Error> {
    let s = std::str::from_utf8(&[240, 159, 141, 137])?;
    Ok(s)
}

fn countdown<F>(count: usize, tick: F)
    where F: Fn(usize)
{
    for i in (1..=count).rev() {
        tick(i);
    }
}

fn make_tester_move(answer: String) -> impl Fn(&str) -> bool {
    move |challenge| {
        challenge == answer
    }
}
// fn make_tester_ref<'a>(answer: &'a str) -> impl Fn(&str) -> bool + 'a {
fn make_tester_ref(answer: &str) -> impl Fn(&str) -> bool + '_ {
    move |challenge| {
        challenge == answer
    }
}

fn main() {
    let _x: i32 = 42;
    let x = 101;
    dummy_print(x);
    let y: i32 = 200;
    dummy_print(y);

    let pair: (i32, i64) = (10, 12);
    dummy_print(pair.0);
    // This is going to explode on an overflow.
    let b: i32 = pair.1.try_into().unwrap();
    dummy_print(b);
    let (a, _) = pair;
    dummy_print(a);

    let x = vec![1, 2, 3, 4, 5, 6, 7, 8]
        .iter()
        .map(|x| x + 3)
        .fold(0, |x, y| x + y);
    dummy_print(x);

    let x = {
        let y = 1;
        let z = 2;
        y + z
    };
    dummy_print(x);
    dummy_print(flip(false));

    let _nick: String = "Nick".to_string();
    let nick: &str = "Nick";
    dummy_print(nick);
    dummy_print(nick.len());

    // use std::cmp::min; -> Tricky to use because you can "override" min.
    let least = std::cmp::min(3, 8);
    dummy_print(least);

    let min = 20;
    dummy_print(min);

    let _v1 = DummyVec { x: 1.0, y: 3.0 };
    let v2 = DummyVec { x: 4.0, y: 2.0 };
    // struct update syntax
    let _v3 = DummyVec { x: 14.0, ..v2 };
    let v = DummyVec { x: 3.0, y: 6.0 };
    // let pattern
    let DummyVec {x, y} = v;
    dummy_print(x);
    dummy_print(y);

    let mut one = Number { odd: true, value: -1 };
    let two = Number { odd: false, value: 2 };
    let three = Number { odd: true, value: 3 };
    one.value = 1;
    print_number_ref(&one);
    print_number_ref(&two);
    print_number_ref(&three);
    dummy_print(one.is_strictly_positive());
    print_number_ref(&three);

    let mut four = Number { odd: false, value: 4 };
    dummy_print(-four.value);
    // The following line will pass because four is not moved in the previous line.
    // If Number the marker trait Copy defined print_number will always pass.
    // print_number(four);
    invert(&mut four);
    dummy_print(four.value);
    print_number(four);

    let four_copy = four;
    print_number(four_copy);
    dummy_print(four_copy);

    println!("{}", std::any::type_name::<(f64, char)>());
    let p1 = Pair { a: 1.0, b: 2.0 };
    print_type_name(&p1);

    let mut v1 = Vec::new();
    v1.push(1);
    let v2 = vec![true, false, true];
    print_type_name(&v2);

    // panic!("This is a panic.");

    let mut x: i32 = 99;
    let x_ref = as_num_ref(&x);
    // x = 100;
    dummy_print(x_ref.x);

    // Arguments lifetime example.
    let n1 = NonCopyNumber { odd: false, value: 1000 };
    let n2 = NonCopyNumber { odd: false, value: 2000 };
    let n3 = number_value(&n1, &n2);
    let n4 = n2;
    dummy_print(n3);
    dummy_print(n4);

    let name = format!("fasterthan{}", "lime");
    let p = RefStrPerson { name: &name };
    dummy_print(p);

    let name = format!("fasterthan{}", "lime");
    let p = Person { name };
    dummy_print(p);
    // dummy_print(name);

    let vec = 1..5;
    print_type_name(&vec);

    // let result = hardcoded_utf8_example();
    let result = hardcoded_utf8_example_short();
    match result {
        Ok(s) => println!("{}", s),
        Err(e) => panic!(e),
    }

    countdown(3, |i| println!("tick {}...", i));
    countdown(3, |_| ());

    let test = make_tester_move("hunter2".into());
    println!("{}", test("******"));
    println!("{}", test("hunter2"));

    let test = make_tester_ref("hunter2");
    println!("{}", test("*******"));
    println!("{}", test("hunter2"));
}

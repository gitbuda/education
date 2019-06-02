// single mutable ownership or multiple readonly aliases at a time
//
// exclusive ownership/borrowing or shared access with multiple aliases being
// active at the same time

struct Person {
    name: String,
    age: i32
}

fn print_person(person: &Person) {
    // person.name = "Fail".to_string();
    println!("PERSON(name: {}, age: {})", person.name, person.age);
}

fn birthday(mut person: Person) -> Person {
    person.age += 1;
    return person;
}

fn main() {
    println!("{} world!", "Hello");
    let test = format!("{}", "String Format");
    println!("{}", test);

    let tom = Person { name: "Tom".to_string(), age: 20 };
    print_person(&tom);

    let tom = birthday(tom);
    print_person(&tom);
}

use std::env;

use std::fs::OpenOptions;
use std::io::{Read, Write};

fn main() -> std::io::Result<()> {
    // get arguments of the command
    let mut args: Vec<String> = env::args().collect();

    // delete the first 1 arguments or else the file name will come
    args.remove(0);

    // add a todo
    if args[0] == "add" {
        let mut list = OpenOptions::new()
            .read(true) // permission to read the file
            .append(true) // permission to append to the file; not the same as write because it does not delete the file's contents
            .open("list.txt") // opens the todo list file
            .unwrap(); // sends an error message

        args.remove(0); // remove the operation on the todo list, in this case "add" so that it loops properly

        // loop through the arguments and append them to the file
        for i in &args {
            let task = format!("{}{}", i, "\n"); // adds a newline (\n) to every todo that needs to be added to the file
            list.write(task.as_bytes())?; // append to the file as bytes. no idea why it needs to be bytes
        }
    }

    // remove a todo
    if args[0] == "rm" {
        args.remove(0);
        let mut list = OpenOptions::new()
            .read(true) // explanation is on the add todo block
            .open("list.txt")
            .unwrap();

        let mut contents = String::new();
        list.read_to_string(&mut contents)?;
        println!("{}", contents);

        let mut list = OpenOptions::new() // shadowing
            .truncate(true) // this line tells to delete the file's contents
            .write(true)
            .open("list.txt")
            .unwrap();

        let replaced = str::replace(&contents, &args[0], ""); // replace the todo with nothing
        list.write_all(replaced.as_bytes())?; // completely write the string with the list to the file
    }

    // edit a todo
    if args[0] == "edit" {
        args.remove(0);
        let mut list = OpenOptions::new()
            .read(true) // explanation is on the add todo block
            .open("list.txt")
            .unwrap();

        let mut contents = String::new();
        list.read_to_string(&mut contents)?;

        let mut list = OpenOptions::new() // shadowing
            .truncate(true) // this line tells to delete the file's contents
            .write(true)
            .open("list.txt")
            .unwrap();

        let replaced = str::replace(&contents, &args[0], &args[1]); // replace the todo with nothing
        list.write_all(replaced.as_bytes())?; // completely write the string with the list to the file
    }

    if args[0] == "list" {
        let mut list = OpenOptions::new()
            .read(true) // explanation is on the add todo block
            .open("list.txt")
            .unwrap();

        let mut contents = String::new();
        list.read_to_string(&mut contents)?;

        let listed = contents.split('\n');

        let listed: Vec<_> = listed.collect();

        let mut counter: i16 = 0;

        for i in listed {
            counter += 1;
            let item = format!("{}. {}", counter, i);
            println!("{}", item);
        }
    }

    Ok(())
}

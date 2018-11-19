Right now, all you're doing is creating a Qml type which you can use as part of your API. To actually _see_ it, you need to create an instance of it under a `ApplicationWindow` or `Window`.

There are two ways you can accomplish this. You can 

 1. Use the item directly.
 2. Save your Qml Progress Bar Item in a separate file, and create an object in an `ApplicationWindow`.

# Code in Action

### Method 1

Directly insert your codeblock as a child of `ApplicationWindow`.

[`MethodOne/Main.qml`](./MethodOne/Main.qml)

### Method 2

Save your item into a new qml file

[`MethodTwo/MyProgressBar.qml`](./MethodTwo/MyProgressBar.qml)

Then call it from your ApplicationWindow in `Main.qml`

[`MethodTwo/Main.qml`](./MethodTwo/Main.qml)

make sure that your qml files are in the same directory. If not, place a `import "file/path"` at the top of the `Main.qml` file among the other import statements.


# Result

This is what the application looks like when I run it on my Mac.

At startup.

[![At startup.][1]][1]

After 3 clicks on the background.

[![After 3 clicks on the background.][2]][2]

There is also console/debug output after each click:

    Progressbar value changed: 10
    Progressbar value changed: 15
    Progressbar value changed: 20


  [1]: ./screenshots/init.png
  [2]: ./screenshots/threeClicks.png
  
----

See also: [_Original StackOverflow Answer_](https://stackoverflow.com/a/53316803/10239789).

# stx::observable

## Header
stdxx/observer.hxx

<br>

---

<br>

## Description
stx::observable implements basic mechanics to make a object observable.

<br>

---

<br>

## Template parameters
| Name    | Info                         | Default |
| ------- | ---------------------------- | ------- |
| Args... | Paramenters for notification | -       |

<br>

---

<br>

## Member functions

<br>

### stx::referece<observer> add_observer(observer observer)

Adds callback as observer.

<br>

### void remove_observer(stx::referece<observer> observer)

Removes observer if already registered. Does nothing if the matching observer is not present.

<br>


### void notify(const Args & ... data)

Sends a notification to all registered observers.

<br>

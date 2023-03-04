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

### void add_observer(std::function&lt;void(const Args &...)&gt; observer)

Adds callback as observer.

<br>

### void notify(const Args & ... data)

Sends a notification to all registered observers.

<br>

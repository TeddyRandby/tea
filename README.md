# TEA

## A React-inspired terminal ui framework.

### Building
```
git clone
cd repo
mkdir build
cd build
cmake ..
make
./sandbox
```

### Docs
#### Components
Tea is a component-based ui library, a familiar concept for ui frameworks.
Similar to React's functional components, The logic of Tea components is driven by an std::function called a Generator.

This std::function has the signature: 

```
void (TComponent &)
```

The component passed into the Generator is the component itself. The generator will run every time the component is rendered.
An example:

```
tea.render([](Tcomponent &c) {
  c.addTitle("Hello world");  
});
```

In this example, "tea" is the larger application. The render method adds a sub component. 

The driving principle of Tea is the following:
#### UI is a function of state.


Building a simple modern 2D engine for simulation projects like simulating ants and possibly other agent based systems (that's where the name is from) and small games. 

## What's implemented so far

* Super simple 2D rendering (WIP)
* Entity-Component-System (ECS)
* Entity Hierarchy (almost a Scene Graph), parent-child relationships between Entities
* Tests for the major modules
* Mouse events at component-level

Demos included:
* cells, a multithreaded Conway's game of life
* orbits, a simple little orbital physics simulation. I wrote this for testing some physics, its really shitty and laggy

## Planned

I'm currently shooting for `1.0`, which will be the MVP, not the finished project. 

Take a look at the [project(s)](https://github.com/lionkor/antsim3/projects)

## Requirements

* `fmt`, included
* `doctest`, included
* `sfml`, currently not included, which will change (probably)

All it will be is a simple lightweight hobby project engine.

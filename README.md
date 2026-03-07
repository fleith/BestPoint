# BestPoint

[![CI](https://github.com/fleith/BestPoint/actions/workflows/ci.yml/badge.svg)](https://github.com/fleith/BestPoint/actions/workflows/ci.yml)

A Genetic Algorithm that finds the optimal 2D point minimising total distance
and spread to a set of base points.

Originally written in 2008 using Borland C++ Builder (VCL GUI).
Rebuilt as a headless CLI using Visual Studio 2022 / MSVC.

---

## Problem

Given a set of base points in a 2D space, BestPoint searches for the
coordinates (x, y) that simultaneously minimise:

- **Total distance** to all base points (weighted by `--fdist`)
- **Spread** (mean absolute deviation of those distances, weighted by `--fdist2`)

The two objectives are combined into a single fitness score:

    fitness = (normalizer * 2 * N) / (totalDist * fdist + meanDev * N * fdist2 + epsilon)

Higher fitness is better. The algorithm evolves a population of candidate
points over multiple generations until the best individual is returned.

---

## Project Structure

    src/                Core GA types
      chromosome        A candidate solution — a 2D point (x, y)
      population        Collection of chromosomes
      fitness           Fitness function (distance + spread)
      selection         Selection strategies (5 methods)
      crossover         Crossover operators (random, sequential)
      mutation          Mutation operator
      math_utils        Euclidean distance and mean deviation
      ga_utils          Helpers (best/worst individual, random generators)

    app/
      app               Application controller — orchestrates the GA loop

    interface/
      ui.h              UI facade — decouples App from display layer
      ui_cli.cpp        CLI implementation of the UI facade
      ui_gui.cpp        VCL/Borland GUI implementation (legacy)

    cli/
      cli_config.h      CLI parameter struct
      main.cpp          CLI entry point

    tests/              Unit test suite (zero-dependency, 55 tests)
    gui/                Borland VCL forms (legacy, requires RAD Studio)

---

## Building (CLI)

Requires **Visual Studio 2022** (Community edition is free).

```bat
build.bat
```

This calls `vcvars64.bat` automatically and produces `BestPoint.exe`.
Run from any terminal: cmd, PowerShell, or Git Bash (`cmd //c build.bat`).

---

## Tests

```bat
build_tests.bat
```

Builds and immediately runs the test suite (`run_tests.exe`). All 55 tests
across 9 modules must pass. Tests are also run automatically on every push
via GitHub Actions.

---

## Running

```
BestPoint.exe [options]

Options:
  -p,  --pop    <n>     Population size          (default: 50)
  -g,  --gen    <n>     Number of generations    (default: 100)
  -c,  --cross  <n>     Crossover rate %         (default: 70)
  -m,  --mut    <n>     Mutation rate %          (default: 10)
       --minx   <n>     Min X bound              (default: 0)
       --maxx   <n>     Max X bound              (default: 100)
       --miny   <n>     Min Y bound              (default: 0)
       --maxy   <n>     Max Y bound              (default: 100)
       --points <n>     Number of base points    (default: 5)
       --sel    <type>  Selection method         (default: truncation)
                          truncation | roulette | rank
                          elitist-replacement | hybrid
       --ctype  <type>  Crossover type           (default: random)
                          random | sequential
       --fdist  <f>     Distance factor          (default: 1.0)
       --fdist2 <f>     Distribution factor      (default: 1.0)
  -h,  --help           Show this help
```

### Examples

```bat
REM Default run
BestPoint.exe

REM Larger search space, more generations, roulette selection
BestPoint.exe -p 100 -g 500 --maxx 500 --maxy 500 --points 10 --sel roulette

REM Emphasise spread over distance
BestPoint.exe --fdist 0.5 --fdist2 2.0

REM Elitist replacement, sequential crossover
BestPoint.exe --sel elitist-replacement --ctype sequential

REM Hybrid: truncation elite + roulette fill
BestPoint.exe --sel hybrid
```

### Output

```
================================================
  BestPoint - Genetic Algorithm
================================================
  Population     : 50
  Generations    : 100
  Crossover      : 70%
  Mutation       : 10%
  Bounds X       : [0, 100]
  Bounds Y       : [0, 100]
  Base points    : 5
  Selection      : truncation
  Crossover type : random
  Dist factor    : 1.00
  Distr factor   : 1.00
================================================
  Base points:
    [1] (23.00, 67.00)
    [2] (45.00, 12.00)
    ...
================================================
  Running 100 generations...
================================================
  Gen    1/100  |  best=    9.8123  worst=    3.4201  avg=    7.2341
  ...
  Gen  100/100  |  best=   10.5163  worst=    7.4716  avg=   10.2168
================================================
  Result
================================================
  Best individual : (31.0000, 41.0000)
================================================
```

---

## Selection Methods

| Name                  | Literature term | Description |
|-----------------------|-----------------|-------------|
| `truncation`          | Truncation Selection (Mühlenbein 1993) | Top 1/3 survive deterministically; remainder re-sampled randomly. Best individual always carried over via elitism. |
| `roulette`            | Fitness-Proportionate Selection / FPS (Holland 1975) | Each individual's selection probability is proportional to its fitness. |
| `rank`                | Linear Rank Selection (Baker 1985) | Selection probability proportional to rank, not raw fitness — avoids dominance by a single high-fitness individual. |
| `elitist-replacement` | Elitist Replacement | Bottom 5% replaced by copies of the top 5%. A replacement strategy rather than a full selection method. |
| `hybrid`              | Hybrid (Truncation + FPS) | Top 1/3 preserved by truncation; remaining 2/3 filled by roulette-wheel selection — combines two literature methods. |

---

## GUI (Legacy)

The original Borland C++ Builder GUI (`gui/`, `AG.bpr`) can be opened with
**Embarcadero RAD Studio** (free Community Edition available at embarcadero.com).
It provides a visual canvas showing individual positions, fitness charts, and
interactive parameter controls.

---

## Requirements

- **CLI build:** Visual Studio 2022 (any edition)
- **GUI build:** Embarcadero RAD Studio (Borland C++ Builder successor)

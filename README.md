# BestPoint

A Genetic Algorithm that finds the optimal 2D point minimising total distance
and spread to a set of base points.

Originally written in 2008 using Borland C++ Builder (VCL GUI).
A CLI build is now available using Visual Studio 2022 / MSVC.

---

## Problem

Given a set of base points in a 2D space, BestPoint searches for the
coordinates (x, y) that simultaneously minimise:

- **Total distance** to all base points (weighted by `--fdist`)
- **Spread** (mean absolute deviation of those distances, weighted by `--fdist2`)

The two objectives are combined into a single fitness score:

    fitness = (normalizador * 2 * N) / (sumDist * fdist + meanDev * fdist2)

Higher fitness is better. The algorithm evolves a population of candidate
points over multiple generations until the best individual is returned.

---

## Project Structure

    Classes/        Core GA types
      Cromossomo     A candidate solution — a 2D point (x, y)
      Populacao      Collection of chromosomes
      Fitness        Fitness function (distance + spread)
      Selecao        Selection strategies
      Crossover      Crossover operators
      Mutacao        Mutation operator
      Calculo        Math utilities (Euclidean distance, mean deviation)

    Util/
      AGUtil         Helpers (best/worst individual, random generators)

    App/
      AppAG          Application controller — orchestrates the GA loop

    Interface/
      GerenteInterfaceAG.h      Facade (GI) — decouples App from UI
      GerenteInterfaceCLI.cpp   CLI implementation of GI
      GerenteInterfaceAG.cpp    VCL/Borland GUI implementation (legacy)

    GUI/             Borland VCL forms (legacy, requires RAD Studio)
    CLI/             CLI entry point and config

---

## Building (CLI)

Requires **Visual Studio 2022** (Community edition is free).

```bat
build.bat
```

This calls `vcvars64.bat` automatically and produces `BestPoint.exe`.
Run from any terminal: cmd, PowerShell, or Git Bash (`cmd //c build.bat`).

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
       --sel    <type>  Selection method         (default: elitismo)
                          elitismo | roleta | classificacao
                          estacionaria | hibrido
       --ctype  <type>  Crossover type           (default: aleatorio)
                          aleatorio | sequencial
       --fdist  <f>     Distance factor          (default: 1.0)
       --fdist2 <f>     Distribution factor      (default: 1.0)
  -h,  --help           Show this help
```

### Examples

```bat
REM Default run
BestPoint.exe

REM Larger search space, more generations, roulette selection
BestPoint.exe -p 100 -g 500 --maxx 500 --maxy 500 --points 10 --sel roleta

REM Emphasise spread over distance
BestPoint.exe --fdist 0.5 --fdist2 2.0

REM Steady-state selection, sequential crossover
BestPoint.exe --sel estacionaria --ctype sequencial
```

### Output

```
================================================
  BestPoint - Genetic Algorithm
================================================
  Population     : 50
  ...
================================================
  Base points:
    [1] (23.00, 67.00)
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

| Name            | Description |
|-----------------|-------------|
| `elitismo`      | Top 1/3 survive; remainder filled randomly. Best individual always carried over. |
| `roleta`        | Roulette-wheel (fitness-proportionate) selection. |
| `classificacao` | Rank-based selection — higher-ranked individuals have proportionally more chances. |
| `estacionaria`  | Steady-state — bottom 5% replaced by copies of the top 5%. |
| `hibrido`       | Top 1/3 duplicated, then random fill (custom hybrid strategy). |

---

## GUI (Legacy)

The original Borland C++ Builder GUI (`GUI/`, `AG.bpr`) can be opened with
**Embarcadero RAD Studio** (free Community Edition available at embarcadero.com).
It provides a visual canvas showing individual positions, fitness charts, and
interactive parameter controls.

---

## Requirements

- **CLI build:** Visual Studio 2022 (any edition)
- **GUI build:** Embarcadero RAD Studio (Borland C++ Builder successor)

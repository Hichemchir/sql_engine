# Minimal SQL Engine

## Overview
The Minimal SQL Engine is a lightweight educational project designed to demonstrate the fundamental architecture of a SQL engine. It provides a basic framework for parsing SQL statements, executing logical plans, and managing data storage. This project serves as a foundation for learning about SQL engine internals and can be extended with more complex features in the future.

## Overview 

In: "SELECT name FROM users WHERE age > 18"
                    ↓
            [SQL engine]
                    ↓
Out: list of filtered names

## What do we need ?
- Storage: to store the data
- Parser: transform the SQL query into sth our code understands
- Planner: decide how to retrieve data (scan, filter, project, etc)
- Executor: do the work
- Optimizer


# To add next:
- aggregations (count, sum, avg, min, max)
- Start SQL Parser (to write real SQL)
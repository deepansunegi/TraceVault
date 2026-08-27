# TraceVault

**TraceVault** is a professional, file-backed command-line evidence and incident tracker written in pure C.

It is designed as a portfolio project that demonstrates more than basic CRUD: persistent storage, SHA-256 integrity hashing, tamper detection, audit logging, search, status workflows, reporting, defensive input validation, modular architecture, and automated tests.

## Why this project stands out

Most beginner C projects are calculators or management systems. TraceVault simulates a small forensic/evidence workflow:

- Create evidence records
- Automatically calculate SHA-256 hashes
- Detect file tampering later
- Track evidence status and chain-of-custody events
- Search records by keyword
- Generate a professional text report
- Persist data between runs
- Maintain an audit log
- Use modular source/header organization
- Build with a Makefile
- Run automated tests

## Build

### Linux / macOS / MinGW
```bash
make
./tracevault
```

Or directly:

```bash
gcc -std=c11 -Wall -Wextra -Wpedantic -O2 -Iinclude src/*.c -o tracevault
```

## Usage

When launched, select:

1. Add evidence
2. List evidence
3. Search evidence
4. Verify evidence integrity
5. Update status
6. Add custody event
7. Generate report
8. View audit log
0. Exit

## Project structure

```text
TraceVault/
├── src/
│   ├── main.c
│   ├── vault.c
│   ├── storage.c
│   ├── sha256.c
│   └── utils.c
├── include/
│   ├── vault.h
│   ├── storage.h
│   ├── sha256.h
│   └── utils.h
├── data/
│   └── .gitkeep
├── tests/
│   └── test_sha256.c
├── Makefile
├── README.md
├── LICENSE
└── .gitignore
```

## Data files

The program creates these files automatically in `data/`:

- `evidence.db` — persistent records
- `audit.log` — append-only activity log
- `report.txt` — generated report

## Resume description

**TraceVault — Secure Evidence & Incident Tracking CLI | C**

Built a modular C application for tracking digital evidence and incident records with persistent file storage, SHA-256 integrity verification, tamper detection, audit logging, search, chain-of-custody tracking, and automated report generation. Implemented defensive input validation and a multi-file architecture using headers, Makefile-based builds, and unit tests.

## Suggested GitHub topics

`c` `cli` `sha256` `cybersecurity` `file-integrity` `systems-programming` `forensics`

## License

MIT License. See [LICENSE](LICENSE).

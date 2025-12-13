# Sensor Calibration Repository

This repository hosts code, documentation and examples for calibrating a variety of sensors used in Project ALtair. The purpose of this repo is to provide reusable sensor drivers, calibration routines,etc. so contributors can reliably calibrate and validate sensor modules across different hardware revisions and environments. Details will be filled in per-sensor as work progresses.

---

## Getting Started + Contributing

1. Pick a sensor folder and read its `README.md` for hardware and software prerequisites.
2. Create a branch for your work: `git checkout -b sensor/<name>/your-feature`.
3. Implement driver, calibration routine, add tests and documentation.
4. Open a Pull Request and request review from the sensor owner.

---
## Sensors

- [Methane Sensor (MQ4)](methane/README.md)
- [Humidity Sensor](humidity/README.md)
- [UV Sensor](uv/README.md)
- [Temperature Sensor](temperature/README.md)
- [Soil Moisture Sensor](soilMoisture/README.md)
- [Ultrasonic Distance Sensor](ultrasonic/README.md)
- [CO Sensors](co/README.md)

More sensors and modules will be added as the project expands; each new sensor should follow the same directory layout and documentation pattern.

---

## Repository Structure

.
├── sensors/
│   ├── methane/
│   ├── humidity/
	│   ├── README.md
│   ├── uv/
	├── temperature/
	├── soilMoisture/
	├── ultrasonic/
	├── co/
	└── ...
└── README.md


Each sensor directory contains:
- Sensor driver code
- Calibration logic (calibration routines, parameter storage)
- A dedicated `README.md` describing hardware setup, calibration, and usage

---



## Development Guidelines

- Each sensor or feature must be developed in its own branch (e.g., `sensor/<name>/feature`)
- All code contributions must include updated documentation and example usage
- Follow consistent naming and folder structure across all modules
- Do not push directly to the `main` branch — use PRs and at least one reviewer

---

## Documentation Policy

- Every major folder contains its own `README.md` explaining hardware wiring, dependencies, and calibration steps
- Sensor-specific calibration notes, measurement conditions, and data formats are maintained inside the respective sensor folder
- Longer-form research, whitepapers, or reference materials should be placed in a `docs/` subfolder and linked from sensor READMEs

---

## Team

This repository is maintained by the Batch 23, Software Subteam of Project ALtair.
Sensor modules are owned and documented by their respective contributors, check each sensor's `README.md` for ownership details.

---

## License

To be decided.

---

> Notes: This README is intentionally brief, each sensor subfolder contains the actionable, sensor-specific documentation.


# Nightlight (nightlight.ino)

An Arduino-based night light that activates 6 LEDs based on input from
a photocell and motion sensor. A timer turns the LEDs off after a period
of inactivity.

The motivation to build this nightlight was the desire for a light that
that would ramp up slowly so not to startle or blind someone used to the
dark, and also ramp down slowly so it wouldn't leave someone suddenly
in the dark if they were still for too long.

The light-on duration, ramp-up, ramp-down, and light threshold (ambient light level below which the
LEDs can be activated) are all, of course, adjustable.


package org.onebeartoe.sht41.trinkey;

/**
 * 
 */
public sealed interface SensorReading permits TemperatureReading, HumidityReading, BadReading {}

record TemperatureReading(float temperature) implements SensorReading {};

record HumidityReading(float humidity) implements SensorReading {};

record BadReading(String line) implements SensorReading {};

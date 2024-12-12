
package org.onebeartoe.sht41.trinkey;

/**
 * 
 */
public sealed interface SensorReading permits TemperatureReading, HumidityReading, BadReading {}

record TemperatureReading(double temperature) implements SensorReading {};

record HumidityReading(double humidity) implements SensorReading {};

record BadReading(double humidity) implements SensorReading {};

package be.webtechie.pi4jgpio.definition;

import java.util.Arrays;
import java.util.List;

public enum AsciiCharacter {
    SPACE(0x20, 2, Arrays.asList(
            (byte) Integer.parseInt("00", 2),
            (byte) Integer.parseInt("00", 2),
            (byte) Integer.parseInt("00", 2),
            (byte) Integer.parseInt("00", 2),
            (byte) Integer.parseInt("00", 2),
            (byte) Integer.parseInt("00", 2),
            (byte) Integer.parseInt("00", 2),
            (byte) Integer.parseInt("00", 2)
    )),
    N_0(0x30, 6, Arrays.asList(
            (byte) Integer.parseInt("011110", 2),
            (byte) Integer.parseInt("100001", 2),
            (byte) Integer.parseInt("100001", 2),
            (byte) Integer.parseInt("100001", 2),
            (byte) Integer.parseInt("100001", 2),
            (byte) Integer.parseInt("100001", 2),
            (byte) Integer.parseInt("100001", 2),
            (byte) Integer.parseInt("011110", 2)
    )),
    N_1(0x31, 6, Arrays.asList(
            (byte) Integer.parseInt("111100", 2),
            (byte) Integer.parseInt("000100", 2),
            (byte) Integer.parseInt("000100", 2),
            (byte) Integer.parseInt("000100", 2),
            (byte) Integer.parseInt("000100", 2),
            (byte) Integer.parseInt("000100", 2),
            (byte) Integer.parseInt("000100", 2),
            (byte) Integer.parseInt("111111", 2)
    )),
    N_2(0x32, 6, Arrays.asList(
            (byte) Integer.parseInt("111111", 2),
            (byte) Integer.parseInt("100001", 2),
            (byte) Integer.parseInt("000001", 2),
            (byte) Integer.parseInt("000010", 2),
            (byte) Integer.parseInt("000100", 2),
            (byte) Integer.parseInt("001000", 2),
            (byte) Integer.parseInt("010000", 2),
            (byte) Integer.parseInt("111111", 2)
    )),
    N_3(0x33, 6, Arrays.asList(
            (byte) Integer.parseInt("011111", 2),
            (byte) Integer.parseInt("000001", 2),
            (byte) Integer.parseInt("000001", 2),
            (byte) Integer.parseInt("001111", 2),
            (byte) Integer.parseInt("000001", 2),
            (byte) Integer.parseInt("000001", 2),
            (byte) Integer.parseInt("000001", 2),
            (byte) Integer.parseInt("111111", 2)
    )),
    N_4(0x34, 6, Arrays.asList(
            (byte) Integer.parseInt("000111", 2),
            (byte) Integer.parseInt("001001", 2),
            (byte) Integer.parseInt("010001", 2),
            (byte) Integer.parseInt("111111", 2),
            (byte) Integer.parseInt("000001", 2),
            (byte) Integer.parseInt("000001", 2),
            (byte) Integer.parseInt("000001", 2),
            (byte) Integer.parseInt("000001", 2)
    )),
    N_5(0x35, 6, Arrays.asList(
            (byte) Integer.parseInt("111111", 2),
            (byte) Integer.parseInt("100000", 2),
            (byte) Integer.parseInt("100000", 2),
            (byte) Integer.parseInt("111111", 2),
            (byte) Integer.parseInt("000001", 2),
            (byte) Integer.parseInt("000001", 2),
            (byte) Integer.parseInt("000001", 2),
            (byte) Integer.parseInt("111111", 2)
    )),
    N_6(0x36, 6, Arrays.asList(
            (byte) Integer.parseInt("111111", 2),
            (byte) Integer.parseInt("100000", 2),
            (byte) Integer.parseInt("100000", 2),
            (byte) Integer.parseInt("111111", 2),
            (byte) Integer.parseInt("100001", 2),
            (byte) Integer.parseInt("100001", 2),
            (byte) Integer.parseInt("100001", 2),
            (byte) Integer.parseInt("111111", 2)
    )),
    N_7(0x47, 6, Arrays.asList(
            (byte) Integer.parseInt("111111", 2),
            (byte) Integer.parseInt("000001", 2),
            (byte) Integer.parseInt("000010", 2),
            (byte) Integer.parseInt("000100", 2),
            (byte) Integer.parseInt("001000", 2),
            (byte) Integer.parseInt("001000", 2),
            (byte) Integer.parseInt("001000", 2),
            (byte) Integer.parseInt("001000", 2)
    )),
    N_8(0x48, 6, Arrays.asList(
            (byte) Integer.parseInt("011110", 2),
            (byte) Integer.parseInt("100001", 2),
            (byte) Integer.parseInt("100001", 2),
            (byte) Integer.parseInt("011110", 2),
            (byte) Integer.parseInt("100001", 2),
            (byte) Integer.parseInt("100001", 2),
            (byte) Integer.parseInt("100001", 2),
            (byte) Integer.parseInt("011110", 2)
    )),
    N_9(0x49, 6, Arrays.asList(
            (byte) Integer.parseInt("011110", 2),
            (byte) Integer.parseInt("100001", 2),
            (byte) Integer.parseInt("100001", 2),
            (byte) Integer.parseInt("011110", 2),
            (byte) Integer.parseInt("000001", 2),
            (byte) Integer.parseInt("000001", 2),
            (byte) Integer.parseInt("100001", 2),
            (byte) Integer.parseInt("011110", 2)
    )),
    A(0x41, 6, Arrays.asList(
            (byte) Integer.parseInt("001100", 2),
            (byte) Integer.parseInt("010010", 2),
            (byte) Integer.parseInt("100010", 2),
            (byte) Integer.parseInt("111111", 2),
            (byte) Integer.parseInt("100001", 2),
            (byte) Integer.parseInt("100001", 2),
            (byte) Integer.parseInt("100001", 2),
            (byte) Integer.parseInt("100001", 2)
    )),
    B(0x42, 6, Arrays.asList(
            (byte) Integer.parseInt("111110", 2),
            (byte) Integer.parseInt("100001", 2),
            (byte) Integer.parseInt("100001", 2),
            (byte) Integer.parseInt("111110", 2),
            (byte) Integer.parseInt("100001", 2),
            (byte) Integer.parseInt("100001", 2),
            (byte) Integer.parseInt("100001", 2),
            (byte) Integer.parseInt("111110", 2)
    )),
    C(0x43, 6, Arrays.asList(
            (byte) Integer.parseInt("011110", 2),
            (byte) Integer.parseInt("100001", 2),
            (byte) Integer.parseInt("100000", 2),
            (byte) Integer.parseInt("100000", 2),
            (byte) Integer.parseInt("100000", 2),
            (byte) Integer.parseInt("100000", 2),
            (byte) Integer.parseInt("100001", 2),
            (byte) Integer.parseInt("011110", 2)
    )),
    D(0x44, 6, Arrays.asList(
            (byte) Integer.parseInt("111110", 2),
            (byte) Integer.parseInt("100001", 2),
            (byte) Integer.parseInt("100001", 2),
            (byte) Integer.parseInt("100001", 2),
            (byte) Integer.parseInt("100001", 2),
            (byte) Integer.parseInt("100001", 2),
            (byte) Integer.parseInt("100001", 2),
            (byte) Integer.parseInt("111110", 2)
    )),
    E(0x45, 6, Arrays.asList(
            (byte) Integer.parseInt("111111", 2),
            (byte) Integer.parseInt("100000", 2),
            (byte) Integer.parseInt("100000", 2),
            (byte) Integer.parseInt("111111", 2),
            (byte) Integer.parseInt("100000", 2),
            (byte) Integer.parseInt("100000", 2),
            (byte) Integer.parseInt("100000", 2),
            (byte) Integer.parseInt("111111", 2)
    )),
    F(0x46, 6, Arrays.asList(
            (byte) Integer.parseInt("111111", 2),
            (byte) Integer.parseInt("100000", 2),
            (byte) Integer.parseInt("100000", 2),
            (byte) Integer.parseInt("111100", 2),
            (byte) Integer.parseInt("100000", 2),
            (byte) Integer.parseInt("100000", 2),
            (byte) Integer.parseInt("100000", 2),
            (byte) Integer.parseInt("100000", 2)
    )),
    G(0x47, 6, Arrays.asList(
            (byte) Integer.parseInt("011110", 2),
            (byte) Integer.parseInt("100001", 2),
            (byte) Integer.parseInt("100000", 2),
            (byte) Integer.parseInt("100000", 2),
            (byte) Integer.parseInt("100111", 2),
            (byte) Integer.parseInt("100001", 2),
            (byte) Integer.parseInt("100001", 2),
            (byte) Integer.parseInt("011110", 2)
    )),
    H(0x48, 3, Arrays.asList(
            (byte) Integer.parseInt("10001", 2),
            (byte) Integer.parseInt("10001", 2),
            (byte) Integer.parseInt("10001", 2),
            (byte) Integer.parseInt("10001", 2),
            (byte) Integer.parseInt("11111", 2),
            (byte) Integer.parseInt("10001", 2),
            (byte) Integer.parseInt("10001", 2),
            (byte) Integer.parseInt("10001", 2)
    )),
    I(0x49, 3, Arrays.asList(
            (byte) Integer.parseInt("111", 2),
            (byte) Integer.parseInt("010", 2),
            (byte) Integer.parseInt("010", 2),
            (byte) Integer.parseInt("010", 2),
            (byte) Integer.parseInt("010", 2),
            (byte) Integer.parseInt("010", 2),
            (byte) Integer.parseInt("010", 2),
            (byte) Integer.parseInt("111", 2)
    )),
    J(0x4A, 6, Arrays.asList(
            (byte) Integer.parseInt("111111", 2),
            (byte) Integer.parseInt("000100", 2),
            (byte) Integer.parseInt("000100", 2),
            (byte) Integer.parseInt("000100", 2),
            (byte) Integer.parseInt("000100", 2),
            (byte) Integer.parseInt("000100", 2),
            (byte) Integer.parseInt("100100", 2),
            (byte) Integer.parseInt("111000", 2)
    )),
    K(0x4B, 6, Arrays.asList(
            (byte) Integer.parseInt("100001", 2),
            (byte) Integer.parseInt("100001", 2),
            (byte) Integer.parseInt("100010", 2),
            (byte) Integer.parseInt("100010", 2),
            (byte) Integer.parseInt("101100", 2),
            (byte) Integer.parseInt("110010", 2),
            (byte) Integer.parseInt("100001", 2),
            (byte) Integer.parseInt("100001", 2)
    )),
    L(0x4C, 6, Arrays.asList(
            (byte) Integer.parseInt("100000", 2),
            (byte) Integer.parseInt("100000", 2),
            (byte) Integer.parseInt("100000", 2),
            (byte) Integer.parseInt("100000", 2),
            (byte) Integer.parseInt("100000", 2),
            (byte) Integer.parseInt("100000", 2),
            (byte) Integer.parseInt("100000", 2),
            (byte) Integer.parseInt("111111", 2)
    )),
    M(0x4D, 7, Arrays.asList(
            (byte) Integer.parseInt("1100011", 2),
            (byte) Integer.parseInt("1010101", 2),
            (byte) Integer.parseInt("1001001", 2),
            (byte) Integer.parseInt("1001001", 2),
            (byte) Integer.parseInt("1000001", 2),
            (byte) Integer.parseInt("1000001", 2),
            (byte) Integer.parseInt("1000001", 2),
            (byte) Integer.parseInt("1000001", 2)
    )),
    N(0x4E, 6, Arrays.asList(
            (byte) Integer.parseInt("110001", 2),
            (byte) Integer.parseInt("101001", 2),
            (byte) Integer.parseInt("101001", 2),
            (byte) Integer.parseInt("101101", 2),
            (byte) Integer.parseInt("100101", 2),
            (byte) Integer.parseInt("100101", 2),
            (byte) Integer.parseInt("100011", 2),
            (byte) Integer.parseInt("100011", 2)
    )),
    O(0x4F, 6, Arrays.asList(
            (byte) Integer.parseInt("011110", 2),
            (byte) Integer.parseInt("100001", 2),
            (byte) Integer.parseInt("100001", 2),
            (byte) Integer.parseInt("100001", 2),
            (byte) Integer.parseInt("100001", 2),
            (byte) Integer.parseInt("100001", 2),
            (byte) Integer.parseInt("100001", 2),
            (byte) Integer.parseInt("011110", 2)
    )),
    P(0x50, 6, Arrays.asList(
            (byte) Integer.parseInt("111110", 2),
            (byte) Integer.parseInt("100001", 2),
            (byte) Integer.parseInt("100001", 2),
            (byte) Integer.parseInt("111110", 2),
            (byte) Integer.parseInt("100000", 2),
            (byte) Integer.parseInt("100000", 2),
            (byte) Integer.parseInt("100000", 2),
            (byte) Integer.parseInt("100000", 2)
    )),
    Q(0x51, 6, Arrays.asList(
            (byte) Integer.parseInt("011110", 2),
            (byte) Integer.parseInt("100001", 2),
            (byte) Integer.parseInt("100001", 2),
            (byte) Integer.parseInt("100001", 2),
            (byte) Integer.parseInt("100101", 2),
            (byte) Integer.parseInt("100101", 2),
            (byte) Integer.parseInt("011110", 2),
            (byte) Integer.parseInt("000001", 2)
    )),
    R(0x52, 6, Arrays.asList(
            (byte) Integer.parseInt("111110", 2),
            (byte) Integer.parseInt("100001", 2),
            (byte) Integer.parseInt("100001", 2),
            (byte) Integer.parseInt("100010", 2),
            (byte) Integer.parseInt("111100", 2),
            (byte) Integer.parseInt("100010", 2),
            (byte) Integer.parseInt("100001", 2),
            (byte) Integer.parseInt("100001", 2)
    )),
    S(0x53, 6, Arrays.asList(
            (byte) Integer.parseInt("011111", 2),
            (byte) Integer.parseInt("100000", 2),
            (byte) Integer.parseInt("100000", 2),
            (byte) Integer.parseInt("011110", 2),
            (byte) Integer.parseInt("000001", 2),
            (byte) Integer.parseInt("000001", 2),
            (byte) Integer.parseInt("000001", 2),
            (byte) Integer.parseInt("111110", 2)
    )),
    T(0x54, 5, Arrays.asList(
            (byte) Integer.parseInt("11111", 2),
            (byte) Integer.parseInt("00100", 2),
            (byte) Integer.parseInt("00100", 2),
            (byte) Integer.parseInt("00100", 2),
            (byte) Integer.parseInt("00100", 2),
            (byte) Integer.parseInt("00100", 2),
            (byte) Integer.parseInt("00100", 2),
            (byte) Integer.parseInt("00100", 2)
    )),
    U(0x55, 6, Arrays.asList(
            (byte) Integer.parseInt("100001", 2),
            (byte) Integer.parseInt("100001", 2),
            (byte) Integer.parseInt("100001", 2),
            (byte) Integer.parseInt("100001", 2),
            (byte) Integer.parseInt("100001", 2),
            (byte) Integer.parseInt("100001", 2),
            (byte) Integer.parseInt("100001", 2),
            (byte) Integer.parseInt("011110", 2)
    )),
    V(0x56, 7, Arrays.asList(
            (byte) Integer.parseInt("1000001", 2),
            (byte) Integer.parseInt("1000001", 2),
            (byte) Integer.parseInt("1000001", 2),
            (byte) Integer.parseInt("1000001", 2),
            (byte) Integer.parseInt("1000001", 2),
            (byte) Integer.parseInt("0100010", 2),
            (byte) Integer.parseInt("0010100", 2),
            (byte) Integer.parseInt("0001000", 2)
    )),
    W(0x57, 7, Arrays.asList(
            (byte) Integer.parseInt("1000001", 2),
            (byte) Integer.parseInt("1000001", 2),
            (byte) Integer.parseInt("1000001", 2),
            (byte) Integer.parseInt("1000001", 2),
            (byte) Integer.parseInt("1000001", 2),
            (byte) Integer.parseInt("1001001", 2),
            (byte) Integer.parseInt("0101010", 2),
            (byte) Integer.parseInt("0010100", 2)
    )),
    X(0x58, 6, Arrays.asList(
            (byte) Integer.parseInt("100001", 2),
            (byte) Integer.parseInt("010010", 2),
            (byte) Integer.parseInt("001100", 2),
            (byte) Integer.parseInt("001100", 2),
            (byte) Integer.parseInt("001100", 2),
            (byte) Integer.parseInt("010010", 2),
            (byte) Integer.parseInt("010010", 2),
            (byte) Integer.parseInt("100001", 2)
    )),
    Y(0x59, 6, Arrays.asList(
            (byte) Integer.parseInt("100001", 2),
            (byte) Integer.parseInt("010010", 2),
            (byte) Integer.parseInt("001100", 2),
            (byte) Integer.parseInt("001100", 2),
            (byte) Integer.parseInt("001100", 2),
            (byte) Integer.parseInt("001100", 2),
            (byte) Integer.parseInt("001100", 2),
            (byte) Integer.parseInt("001100", 2)
    )),
    Z(0x5A, 6, Arrays.asList(
            (byte) Integer.parseInt("111111", 2),
            (byte) Integer.parseInt("000010", 2),
            (byte) Integer.parseInt("000100", 2),
            (byte) Integer.parseInt("001000", 2),
            (byte) Integer.parseInt("010000", 2),
            (byte) Integer.parseInt("100000", 2),
            (byte) Integer.parseInt("100000", 2),
            (byte) Integer.parseInt("111111", 2)
    )),        ;

    private final int ascii;
    private final int numberOfColumns;
    private final List<Byte> rows;

    AsciiCharacter(int ascii, int numberOfColumns, List<Byte> rows) {
        this.ascii = ascii;
        this.numberOfColumns = numberOfColumns;
        this.rows = rows;
    }

    public int getAscii() {
        return ascii;
    }

    public int getNumberOfColumns() {
        return numberOfColumns;
    }

    public List<Byte> getRows() {
        return rows;
    }

    public static AsciiCharacter getByAscii(int ascii) {
        for (AsciiCharacter asciiCharacter : AsciiCharacter.values()) {
            if (asciiCharacter.getAscii() == ascii) {
                return asciiCharacter;
            }
        }
        return null;
    }

    public static AsciiCharacter getByChar(char character) {
        return getByAscii(character);
    }
}

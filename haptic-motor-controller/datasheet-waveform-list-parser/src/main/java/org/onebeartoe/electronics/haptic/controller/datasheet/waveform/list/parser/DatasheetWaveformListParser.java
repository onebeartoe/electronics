
package org.onebeartoe.electronics.haptic.controller.datasheet.waveform.list.parser;

import java.io.File;
import java.util.Arrays;
import java.util.Collections;
import java.util.HashMap;
import java.util.List;
import java.util.Map;
import java.util.Set;
import java.util.logging.Level;
import java.util.logging.Logger;
import org.jsoup.Jsoup;
import org.jsoup.nodes.Document;
import org.jsoup.nodes.Element;
import org.jsoup.select.Elements;
import org.onebeartoe.io.TextFileReader;
import org.onebeartoe.io.buffered.BufferedTextFileReader;

/**
 * @author Roberto Marquez
 */
public class DatasheetWaveformListParser
{
    public static void main(String[] args) throws Exception
    {
        String infilePath = "../DRV2605 _ Motor-Haptic-Driver-Waveform-List.html";
        File infile = new File(infilePath);

        if (!infile.exists())
        {
            throw new IllegalArgumentException("The infile does not exists: " + infilePath);
        }
        else
        {
            parseList(infilePath);
        }
    }

    private static void parseList(String infilePath)
    {
        TextFileReader textReader = new BufferedTextFileReader();
        String html = textReader.readText(infilePath);

        Document doc = Jsoup.parse(html);
        Elements tables = doc.select("table");
        Element table = tables.get(0);

        Elements trs = table.select("tr");

        String[][] trtd = new String[trs.size()][];
        for (int i = 0; i < trs.size(); i++)
        {
            Elements tds = trs.get(i).select("td");
            trtd[i] = new String[tds.size()];
            for (int j = 0; j < tds.size(); j++)
            {
                trtd[i][j] = tds.get(j).text();
            }
        }

        Logger logger = Logger.getLogger( "datasheet-logger");
        
        Map<Integer, String> map = new HashMap();

        // trtd now contains a multidemtional array with econtents bing the text value of the HTML table.
        // each row has 8 elements 3 sets of namevalue pairs and two separators sub-elements.
        // the data has this format per row:
        //  0       1       2       3       4       5       6       7
        //  id_1    name_1  spacer  id_2    name_2  spacer  id_3    name 3
        for (String[] row : trtd)
        {
            // validate the data in the current row
            if (row.length != 8)
            {
                List<String> list = Arrays.asList(row);
                StringBuilder line = new StringBuilder();

                list.forEach((s) -> line.append(s + "\n"));

                String message = "Bad data, row length " + row.length + ":\n" + line.toString();
                logger.log(Level.SEVERE, message);
            }
            else
            {
                map.put(Integer.valueOf(row[0]), row[1]);

                // skip row 3, it is empty
                map.put(Integer.valueOf(row[3]), row[4]);

                // skip row 5, it is empty
                map.put(Integer.valueOf(row[6]), row[7]);
            }
        }

        Set<Integer> keySet = map.keySet();
        Integer[] a = keySet.toArray(new Integer[0]);
        List<Integer> list = Arrays.asList(a);
        Collections.sort(list);

        list.stream()
            .forEach( i -> 
            {
                String name = map.get(i);
                String waveform = "map.put(" + i + ", " + "\"" + name + "\"" + ");";

                logger.log(Level.INFO, waveform);
            });
    }

    public static Map<Integer, String> hardcodedWaveforms()
    {
        Map map = new HashMap();

        map.put(1, "Strong Click - 100%");
        map.put(2, "Strong Click - 60%");
        map.put(3, "Strong Click - 30%");
        map.put(4, "Sharp Click - 100%");
        map.put(5, "Sharp Click - 60%");
        map.put(6, "Sharp Click - 30%");
        map.put(7, "Soft Bump - 100%");
        map.put(8, "Soft Bump - 60%");
        map.put(9, "Soft Bump - 30%");
        map.put(10, "Double Click - 100%");
        map.put(11, "Double Click - 60%");
        map.put(12, "Triple Click - 100%");
        map.put(13, "Soft Fuzz - 60%");
        map.put(14, "Strong Buzz - 100%");
        map.put(15, "750 ms Alert 100%");
        map.put(16, "1000 ms Alert 100%");
        map.put(17, "Strong Click 1 - 100%");
        map.put(18, "Strong Click 2 - 80%");
        map.put(19, "Strong Click 3 - 60%");
        map.put(20, "Strong Click 4 - 30%");
        map.put(21, "Medium Click 1 - 100%");
        map.put(22, "Medium Click 2 - 80%");
        map.put(23, "Medium Click 3 - 60%");
        map.put(24, "Sharp Tick 1 - 100%");
        map.put(25, "Sharp Tick 2 - 80%");
        map.put(26, "Sharp Tick 3 – 60%");
        map.put(27, "Short Double Click Strong 1 – 100%");
        map.put(28, "Short Double Click Strong 2 – 80%");
        map.put(29, "Short Double Click Strong 3 – 60%");
        map.put(30, "Short Double Click Strong 4 – 30%");
        map.put(31, "Short Double Click Medium 1 – 100%");
        map.put(32, "Short Double Click Medium 2 – 80%");
        map.put(33, "Short Double Click Medium 3 – 60%");
        map.put(34, "Short Double Sharp Tick 1 – 100%");
        map.put(35, "Short Double Sharp Tick 2 – 80%");
        map.put(36, "Short Double Sharp Tick 3 – 60%");
        map.put(37, "Long Double Sharp Click Strong 1 – 100%");
        map.put(38, "Long Double Sharp Click Strong 2 – 80%");
        map.put(39, "Long Double Sharp Click Strong 3 – 60%");
        map.put(40, "Long Double Sharp Click Strong 4 – 30%");
        map.put(41, "Long Double Sharp Click Medium 1 – 100%");
        map.put(42, "Long Double Sharp Click Medium 2 – 80%");
        map.put(43, "Long Double Sharp Click Medium 3 – 60%");
        map.put(44, "Long Double Sharp Tick 1 – 100%");
        map.put(45, "Long Double Sharp Tick 2 – 80%");
        map.put(46, "Long Double Sharp Tick 3 – 60%");
        map.put(47, "Buzz 1 – 100%");
        map.put(48, "Buzz 2 – 80%");
        map.put(49, "Buzz 3 – 60%");
        map.put(50, "Buzz 4 – 40%");
        map.put(51, "Buzz 5 – 20%");
        map.put(52, "Pulsing Strong 1 – 100%");
        map.put(53, "Pulsing Strong 2 – 60%");
        map.put(54, "Pulsing Medium 1 – 100%");
        map.put(55, "Pulsing Medium 2 – 60%");
        map.put(56, "Pulsing Sharp 1 – 100%");
        map.put(57, "Pulsing Sharp 2 – 60%");
        map.put(58, "Transition Click 1 – 100%");
        map.put(59, "Transition Click 2 – 80%");
        map.put(60, "Transition Click 3 – 60%");
        map.put(61, "Transition Click 4 – 40%");
        map.put(62, "Transition Click 5 – 20%");
        map.put(63, "Transition Click 6 – 10%");
        map.put(64, "Transition Hum 1 – 100%");
        map.put(65, "Transition Hum 2 – 80%");
        map.put(66, "Transition Hum 3 – 60%");
        map.put(67, "Transition Hum 4 – 40%");
        map.put(68, "Transition Hum 5 – 20%");
        map.put(69, "Transition Hum 6 – 10%");
        map.put(70, "Transition Ramp Down Long Smooth 1 – 100 to 0%");
        map.put(71, "Transition Ramp Down Long Smooth 2 – 100 to 0%");
        map.put(72, "Transition Ramp Down Medium Smooth 1 – 100 to 0%");
        map.put(73, "Transition Ramp Down Medium Smooth 2 – 100 to 0%");
        map.put(74, "Transition Ramp Down Short Smooth 1 – 100 to 0%");
        map.put(75, "Transition Ramp Down Short Smooth 2 – 100 to 0%");
        map.put(76, "Transition Ramp Down Long Sharp 1 – 100 to 0%");
        map.put(77, "Transition Ramp Down Long Sharp 2 – 100 to 0%");
        map.put(78, "Transition Ramp Down Medium Sharp 1 – 100 to 0%");
        map.put(79, "Transition Ramp Down Medium Sharp 2 – 100 to 0%");
        map.put(80, "Transition Ramp Down Short Sharp 1 – 100 to 0%");
        map.put(81, "Transition Ramp Down Short Sharp 2 – 100 to 0%");
        map.put(82, "Transition Ramp Up Long Smooth 1 – 0 to 100%");
        map.put(83, "Transition Ramp Up Long Smooth 2 – 0 to 100%");
        map.put(84, "Transition Ramp Up Medium Smooth 1 – 0 to 100%");
        map.put(85, "Transition Ramp Up Medium Smooth 2 – 0 to 100%");
        map.put(86, "Transition Ramp Up Short Smooth 1 – 0 to 100%");
        map.put(87, "Transition Ramp Up Short Smooth 2 – 0 to 100%");
        map.put(88, "Transition Ramp Up Long Sharp 1 – 0 to 100%");
        map.put(89, "Transition Ramp Up Long Sharp 2 – 0 to 100%");
        map.put(90, "Transition Ramp Up Medium Sharp 1 – 0 to 100%");
        map.put(91, "Transition Ramp Up Medium Sharp 2 – 0 to 100%");
        map.put(92, "Transition Ramp Up Short Sharp 1 – 0 to 100%");
        map.put(93, "Transition Ramp Up Short Sharp 2 – 0 to 100%");
        map.put(94, "Transition Ramp Down Long Smooth 1 – 50 to 0%");
        map.put(95, "Transition Ramp Down Long Smooth 2 – 50 to 0%");
        map.put(96, "Transition Ramp Down Medium Smooth 1 – 50 to 0%");
        map.put(97, "Transition Ramp Down Medium Smooth 2 – 50 to 0%");
        map.put(98, "Transition Ramp Down Short Smooth 1 – 50 to 0%");
        map.put(99, "Transition Ramp Down Short Smooth 2 – 50 to 0%");
        map.put(100, "Transition Ramp Down Long Sharp 1 – 50 to 0%");
        map.put(101, "Transition Ramp Down Long Sharp 2 – 50 to 0%");
        map.put(102, "Transition Ramp Down Medium Sharp 1 – 50 to 0%");
        map.put(103, "Transition Ramp Down Medium Sharp 2 – 50 to 0%");
        map.put(104, "Transition Ramp Down Short Sharp 1 – 50 to 0%");
        map.put(105, "Transition Ramp Down Short Sharp 2 – 50 to 0%");
        map.put(106, "Transition Ramp Up Long Smooth 1 – 0 to 50%");
        map.put(107, "Transition Ramp Up Long Smooth 2 – 0 to 50%");
        map.put(108, "Transition Ramp Up Medium Smooth 1 – 0 to 50%");
        map.put(109, "Transition Ramp Up Medium Smooth 2 – 0 to 50%");
        map.put(110, "Transition Ramp Up Short Smooth 1 – 0 to 50%");
        map.put(111, "Transition Ramp Up Short Smooth 2 – 0 to 50%");
        map.put(112, "Transition Ramp Up Long Sharp 1 – 0 to 50%");
        map.put(113, "Transition Ramp Up Long Sharp 2 – 0 to 50%");
        map.put(114, "Transition Ramp Up Medium Sharp 1 – 0 to 50%");
        map.put(115, "Transition Ramp Up Medium Sharp 2 – 0 to 50%");
        map.put(116, "Transition Ramp Up Short Sharp 1 – 0 to 50%");
        map.put(117, "Transition Ramp Up Short Sharp 2 – 0 to 50%");
        map.put(118, "Long buzz for programmatic stopping – 100%");
        map.put(119, "Smooth Hum 1 (No kick or brake pulse) – 50%");
        map.put(120, "Smooth Hum 2 (No kick or brake pulse) – 40%");
        map.put(121, "Smooth Hum 3 (No kick or brake pulse) – 30%");
        map.put(122, "Smooth Hum 4 (No kick or brake pulse) – 20%");
        map.put(123, "Smooth Hum 5 (No kick or brake pulse) – 10%");

        return map;
    }
}

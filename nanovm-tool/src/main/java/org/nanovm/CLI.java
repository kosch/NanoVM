package org.nanovm;


import org.apache.commons.cli.*;
import org.apache.log4j.ConsoleAppender;
import org.apache.log4j.Level;
import org.apache.log4j.Logger;
import org.apache.log4j.PatternLayout;
import org.nanovm.converter.*;
import org.nanovm.converter.ClassLoader;

import java.io.File;
import java.io.FileOutputStream;
import java.io.OutputStream;

public class CLI {

    static {
        PatternLayout layout = new PatternLayout("%-5p [%t]: %m%n");
        Logger l = Logger.getLogger("org.nanovm");
        l.setLevel(Level.ERROR);
        l.addAppender(new ConsoleAppender(layout));
    }

    private final static Logger Tracer = Logger.getLogger(CLI.class);

    private static Option OPTION_HELP = OptionBuilder.withLongOpt("help").withDescription("prints this help and exit").create("h");
    private static Option OPTION_CLASSPATH = OptionBuilder.withLongOpt("classpath").withArgName("dir").hasArg().withDescription("path to Java classes").create(null);
    private static Option OPTION_CLASS = OptionBuilder.withLongOpt("class").withArgName("name").hasArg().withDescription("Java class name for compilation").create(null);
    private static Option OPTION_LIMIT = OptionBuilder.withLongOpt("limit").withArgName("size").hasArg().withDescription("Limit byte code size in bytes").create(null);
    private static Option OPTION_DEST = OptionBuilder.withLongOpt("dest").withArgName("dir").hasArg().withDescription("Output directory for results").create(null);
    private static Option OPTION_DEBUG = OptionBuilder.withLongOpt("debug").withDescription("Enable debug output").create("d");

    public static void main(String[] args) throws ClassNotFoundException {

        Options options = new Options();
        options.addOption(OPTION_HELP);
        options.addOption(OPTION_CLASSPATH);
        options.addOption(OPTION_CLASS);
        options.addOption(OPTION_LIMIT);
        options.addOption(OPTION_DEST);
        options.addOption(OPTION_DEBUG);
        try {

            CommandLineParser parser = new PosixParser();
            CommandLine cmd = parser.parse( options, args);

            if(cmd.hasOption(OPTION_HELP.getLongOpt())){
                printUsage(options);
                System.exit(0);
            }

            if(cmd.hasOption(OPTION_DEBUG.getLongOpt())){
                Logger l = Logger.getLogger("org.nanovm");
                l.setLevel(Level.ALL);
            }

            if(cmd.hasOption(OPTION_CLASS.getLongOpt())){
                String classPath = "";
                if(cmd.hasOption(OPTION_CLASSPATH.getLongOpt())){
                    classPath = cmd.getOptionValue(OPTION_CLASSPATH.getLongOpt());
                }

                int limit = 512;
                if(cmd.hasOption(OPTION_LIMIT.getLongOpt())){
                    try {
                        limit = Integer.parseInt(cmd.getOptionValue(OPTION_LIMIT.getLongOpt()));
                    } catch (Throwable t){
                        Tracer.debug(t);
                    }
                }

                File destDir = new File("");
                if(cmd.hasOption(OPTION_DEST.getLongOpt())){
                    destDir = new File(cmd.getOptionValue(OPTION_DEST.getLongOpt()));
                    if(!destDir.isDirectory()){
                        throw new MissingOptionException("Destination directory not exists.");
                    }
                }
                Tracer.debug("Output directory "+destDir.getAbsolutePath());

                ClassLoader cl = new ClassLoader(classPath);
                cl.getClassInfo(cmd.getOptionValue(OPTION_CLASS.getLongOpt()));

                Converter c = new Converter(cl, limit);
                byte[] nvmData = c.toByteArray();

                String classNamePath = cmd.getOptionValue(OPTION_CLASS.getLongOpt()).replace('.', '/');
                int lastIndex = classNamePath.lastIndexOf('/');


                if(lastIndex > 0){
                    destDir = new File(destDir, classNamePath.substring(0, lastIndex));
                    destDir.mkdirs();
                }

                File outputFile;
                if(lastIndex > 0){
                    outputFile = new File(destDir, classNamePath.substring(lastIndex, classNamePath.length())+".nvm");
                } else {
                    outputFile = new File(destDir.getAbsolutePath(), classNamePath+".nvm");
                }
                Tracer.debug("Output file: "+outputFile.getAbsolutePath());
                OutputStream os = null;
                try {
                    os= new FileOutputStream(outputFile);
                    os.write(nvmData);
                    os.flush();
                } catch (Throwable t){
                    Tracer.error(t);
                } finally {
                    if(os != null){
                        try { os.close(); } catch(Throwable t){}
                    }
                }
            } else {
                throw new MissingOptionException("Missing class name for converting.");
            }
        } catch(ParseException ex){
            Tracer.error(ex.getMessage());
            Tracer.debug(ex);
            printUsage(options);
        } catch (Exception ex){
            Tracer.error(ex);
ex.printStackTrace();
        }

    }

    private static void printUsage(Options ops){
        HelpFormatter formatter = new HelpFormatter();
        formatter.printHelp(
                "java -jar nanovm-cli.jar [OPTION]",
                "NanoVM Command Line Interface " + Version.version + " - (c) 2005-2007 by Till Harbaum",
                ops,
                ""
        );
    }

}

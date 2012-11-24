package org.nanovm.converter;


import javassist.ClassPool;
import javassist.CtClass;
import javassist.CtConstructor;
import javassist.CtMethod;

import org.apache.log4j.Logger;

import java.io.*;

import java.util.*;
import java.util.jar.JarFile;
import java.util.zip.ZipEntry;
import java.util.zip.ZipFile;

import nanovm.Native;

public class ClassLoader {

    private static final Logger Tracer = Logger.getLogger(ClassLoader.class);

    private List<File> classPath = new ArrayList<File>(1);

    private Vector<ClassInfo> classes = new Vector<ClassInfo>();

    private Vector<NativeClass> nativeClasses = new Vector<NativeClass>();
    private Vector<NativeMethod> nativeMethods = new Vector<NativeMethod>();
    private Vector<NativeField> nativeFields = new Vector<NativeField>();
    public int lowestNativeId = 9999;  // lowest native class id

    // java doesn't have native classes, but we do
    class NativeClass {
        String className;
        int id;

        @Override
        public boolean equals(Object o) {
            if (this == o) return true;
            if (o == null || getClass() != o.getClass()) return false;

            NativeClass that = (NativeClass) o;

            if (id != that.id) return false;
            if (className != null ? !className.equals(that.className) : that.className != null) return false;

            return true;
        }

        @Override
        public int hashCode() {
            int result = className != null ? className.hashCode() : 0;
            result = 31 * result + id;
            return result;
        }

        @Override
        public String toString() {
            return "NativeClass{" +
                    "className='" + className + '\'' +
                    ", id=" + id +
                    '}';
        }
    }

    class NativeMethod {
        String className;
        String name;
        String type;
        int id;

        @Override
        public boolean equals(Object o) {
            if (this == o) return true;
            if (o == null || getClass() != o.getClass()) return false;

            NativeMethod that = (NativeMethod) o;

            if (id != that.id) return false;
            if (className != null ? !className.equals(that.className) : that.className != null) return false;
            if (name != null ? !name.equals(that.name) : that.name != null) return false;
            if (type != null ? !type.equals(that.type) : that.type != null) return false;

            return true;
        }

        @Override
        public int hashCode() {
            int result = className != null ? className.hashCode() : 0;
            result = 31 * result + (name != null ? name.hashCode() : 0);
            result = 31 * result + (type != null ? type.hashCode() : 0);
            result = 31 * result + id;
            return result;
        }

        @Override
        public String toString() {
            return "NativeMethod{" +
                    "className='" + className + '\'' +
                    ", name='" + name + '\'' +
                    ", type='" + type + '\'' +
                    ", id=" + id +
                    '}';
        }
    }

    class NativeField {
        String className;
        String name;
        String type;
        int id;
    }


    public ClassLoader(String classPath) throws ClassNotFoundException {
        Tracer.debug("Classpath: "+classPath);
        StringTokenizer pathTokenizer = new StringTokenizer(classPath, File.pathSeparator);
        while (pathTokenizer.hasMoreElements()) {
            this.classPath.add(new File(pathTokenizer.nextToken()));
        }

        loadNativeClass("java.lang.Object");
    }

    public ClassInfo getClassInfo(String className) throws ClassNotFoundException {
        for(ClassInfo ci : classes){
            if(ci.getName().equals(className)){
                return ci;
            }
        }
        return loadClass(className);
    }

    public ClassInfo getClassInfo(int index){
        return classes.elementAt(index);
    }

    public int getClassIndex(String className){
        // search through all classes
        for (int i = 0; i < classes.size(); i++) {
            if (getClassInfo(i).getName().equals(className))
                return i;
        }
        return -1;
    }

    // in an uvm file all methods of all classes are stored after each other
    // this method returns the class index from the method index in this list
    public ClassInfo getClassInfoFromMethodIndex(int index) {
        int classIndex = 0;

        // search through all classes
        while (index >= getClassInfo(classIndex).methods())
            index -= getClassInfo(classIndex++).methods();

        return getClassInfo(classIndex);
    }


    // get class index of method with index
    public int getClassIndex(int index) {
        int i = 0;

        // search through all classes
        while (index >= getClassInfo(i).methods())
            index -= getClassInfo(i++).methods();

        return i;
    }

    public int totalClasses() {
        return classes.size();
    }

    // return index of main method (must be in class 0, since
    // it is the one the user gave as an argument)
    public int getMainIndex() {
        return getClassInfo(0).getMethodIndex("main", "([Ljava/lang/String;)V");
    }

    public String getSuperClassName(String className) {
        // search through all classes
        for (int i = 0; i < classes.size(); i++) {
            ClassInfo classInfo = getClassInfo(i);

            if (classInfo.getName().equals(className))
                return classInfo.getSuperClassName();
        }
        return null;
    }

    public boolean fieldExistsExact(String className, String name, String type) {
        // search through all classes
        for (int i = 0; i < classes.size(); i++) {
            ClassInfo classInfo = getClassInfo(i);

            if (classInfo.getName().equals(className) && classInfo.providesField(name, type)){
                return true;
            }
        }
        return false;
    }

    public boolean fieldExists(String className, String name, String type) {
        while (className != null) {
            if (fieldExistsExact(className, name, type))
                return true;
            className = getSuperClassName(className);
        }
        return false;
    }

    public FieldInfo getFieldInfoExact(String className, String name, String type) {
        // search through all classes
        for (int i = 0; i < classes.size(); i++) {
            ClassInfo classInfo = getClassInfo(i);

            if (classInfo.getName().equals(className)){
                return classInfo.getFieldInfo(name, type);
            }
        }
        return null;
    }

    public FieldInfo getFieldInfo(String className, String name, String type) {
        while (className != null) {
            FieldInfo result = getFieldInfoExact(className, name, type);
            if (result != null){
                return result;
            }
            className = getSuperClassName(className);
        }
        return null;
    }

    // search for a static field and sum up all static fields before,
    // this gives us the offset to this static field in the table
    // of all static fields of our set of class files
    public int getStaticFieldIndex(String className, String name, String type) {
        // search through all classes
        for (int i = 0, cnt = 0; i < classes.size(); i++) {
            ClassInfo classInfo = getClassInfo(i);

            if (classInfo.getName().equals(className)){
                return cnt + classInfo.getFieldIndex(AccessFlags.STATIC, name, type);
            } else {
                cnt += classInfo.staticFields();
            }
        }
        return -1;
    }

    // search through all classes and return index of matching method
    public int getMethodIndex(String className, String name, String type) {
        for (int i = 0, index = 0; i < classes.size(); i++) {
            if (getClassInfo(i).getName().equals(className)) {
                index += getClassInfo(i).getMethodIndex(name, type);
                return index;
            } else
                index += getClassInfo(i).methods();
        }
        return -1;
    }

    public boolean methodExists(String className,
                                       String name, String type) {
        Tracer.debug("methodExists CN:"+className+" Name:"+name+" Type:"+type);
        // search through all classes


        for (int i = 0; i < classes.size(); i++) {
            ClassInfo classInfo = getClassInfo(i);

            if (classInfo.getName().equals(className) &&
                    classInfo.providesMethod(name, type))
                return true;
        }
        return false;
    }

    public MethodInfo getMethod(int index) {
        int i = 0;

        // search through all classes
        while (index >= getClassInfo(i).methods())
            index -= getClassInfo(i++).methods();

        return getClassInfo(i).getMethod(index);
    }

    // get total methods of all classes
    public int totalMethods() {
        int num = 0;

        for (int i = 0; i < classes.size(); i++)
            num += getClassInfo(i).methods();

        return num;
    }

    // TODO:
    public int totalConstantEntries() {
        int sum = 0;

        for (int i = 0; i < classes.size(); i++)
            sum += getClassInfo(i).getConstPool().totalConstantEntries();

        return sum;
    }

    public int getConstantEntry(int index) {
        int i = 0;

        // search through all classes
        while (index >= getClassInfo(i).getConstPool().totalConstantEntries())
            index -= getClassInfo(i++).getConstPool().totalConstantEntries();

        return getClassInfo(i).getConstPool().getConstantEntry(index);
    }


    // get memory required to store all strings
    public int totalStringSize() {
        int sum = 0;

        for (int i = 0; i < classes.size(); i++)
            sum += getClassInfo(i).getConstPool().totalStringSize();

        return sum;
    }

    // get memory required to store all strings
    public int totalStrings() {
        int sum = 0;

        for (int i = 0; i < classes.size(); i++)
            sum += getClassInfo(i).getConstPool().totalStrings();

        return sum;
    }

    public String getString(int index) {
        int i = 0;

        // search through all classes
        while (index >= getClassInfo(i).getConstPool().totalStrings())
            index -= getClassInfo(i++).getConstPool().totalStrings();

        return getClassInfo(i).getConstPool().getString(index);
    }

    // total number of static fields
    public int totalStaticFields() {
        int sum = 0;

        for (int i = 0; i < classes.size(); i++) {
            ClassInfo classInfo = getClassInfo(i);
            sum += classInfo.staticFields();
        }
        return sum;
    }

    /**
     * loads resource from cp
     * @param name
     * @return
     */
    byte[] loadResource(List<File> classPath, String name){
        Tracer.debug("loadResource "+name);
        byte[] resourceData = null;
        for(File dir : classPath){
            if(dir.isDirectory()){
                Tracer.debug("Check directory "+dir.getAbsolutePath());
                File cf = new File(dir, name);
                if(cf.isFile()){
                    // read single file
                    Tracer.debug("Found file "+cf.getAbsolutePath());
                    FileInputStream fis = null;
                    try {
                        resourceData = readStream(fis = new FileInputStream(cf));
                    } catch (Throwable t){
                        Tracer.error("Failed reading file", t);
                    } finally {
                        if(cf != null){
                            try { fis.close(); } catch (Throwable t){}
                        }
                    }
                }
            } else if(dir.isFile()){
                Tracer.debug("Check archive "+dir.getAbsolutePath());
                JarFile jf = null;
                try {
                    jf = new JarFile(dir, false, ZipFile.OPEN_READ);
                    ZipEntry entry = jf.getEntry(name);
                    if(entry != null){
                        Tracer.debug("Found entry "+name);
                        resourceData = readStream(jf.getInputStream(entry));
                    }
                } catch (Throwable t){
                    Tracer.error("Failed accessing archive", t);
                } finally {
                    if(jf != null){
                        try { jf.close(); } catch (Throwable t){}
                    }
                }
            } else {
                Tracer.debug("Unknown path "+dir.getAbsolutePath());
            }
            if(resourceData != null){
                break;
            }
        }
        return resourceData;
    }

    private ClassInfo loadClass(String name) throws ClassNotFoundException {
        // not loaded already...
        String filePath = name.replace('.', '/')+".class";
        Tracer.debug("loadClass "+filePath);
        byte[] classData = loadResource(classPath, filePath);
        if(classData == null){
            throw new ClassNotFoundException(name);
        }
        ClassFileReader reader = new ClassFileReader();
        ClassInfo info = new ClassInfo(this);
        try {
            reader.read(new ByteArrayInputStream(classData), info);
        } catch (IOException ex){
            throw new ClassNotFoundException(name, ex);
        }
        classes.add(info);

        // go through all constants and check for method references
        info.getConstPool().resolveMethodRefs();

        return info;
    }

    private byte[] readStream(InputStream is) throws IOException {
        if(is == null){
            return null;
        }
        try {
            ByteArrayOutputStream bos = new ByteArrayOutputStream(is.available());
            byte[] buffer = new byte[1024];
            int read;
            while((read = is.read(buffer)) != -1){
                bos.write(buffer, 0, read);
            }
            return bos.size() > 0 ? bos.toByteArray() : null;
        } finally {
            try { is.close(); } catch(Throwable t){}
        }
    }


    public NativeClass getNativeClass(String className) throws ClassNotFoundException {
        Tracer.debug("getNativeClass "+className);
        for(NativeClass nc : nativeClasses){
            if(nc.className.equals(className)){
                return nc;
            }
        }
        Tracer.debug("Try loading native...");
        return loadNativeClass(className);
    }

    public boolean methodIsNative(String className,
                                         String name, String type) {
        Tracer.debug("methodIsNative "+className+" "+name+" "+type);
        try {
            getNativeClass(className);
        } catch (ClassNotFoundException ex){
            Tracer.debug("No native found, return false.");
            return false;
        }
        // search through all native methods
        for (int i = 0; i < nativeMethods.size(); i++) {
            NativeMethod nativeMethod = nativeMethods.elementAt(i);

            Tracer.debug("Check native method: "+nativeMethod);
            // check if we have a match
            if ((className.equals(nativeMethod.className)) &&
                    (name.equals(nativeMethod.name)) &&
                    (type.equals(nativeMethod.type)))

                return true;
        }

        return false;
    }

    public int getNativeMethodId(String className,
                                        String name, String type) {
        try {
            getNativeClass(className);
        } catch (ClassNotFoundException ex){
            return -1;
        }
        // search through all native methods
        for (int i = 0; i < nativeMethods.size(); i++) {
            NativeMethod nativeMethod = nativeMethods.elementAt(i);

            // check if we have a match
            if ((className.equals(nativeMethod.className)) &&
                    (name.equals(nativeMethod.name)) &&
                    (type.equals(nativeMethod.type)))

                return nativeMethod.id;
        }

        return -1;
    }

    public int getNativeFieldId(String className,
                                       String name, String type) {
        try {
            getNativeClass(className);
        } catch (ClassNotFoundException ex){
            return -1;
        }
        // search through all native fields
        for (int i = 0; i < nativeFields.size(); i++) {
            NativeField nativeField = nativeFields.elementAt(i);

            // check if we have a match
            if ((className.equals(nativeField.className)) &&
                    (name.equals(nativeField.name)) &&
                    (type.equals(nativeField.type)))

                return nativeField.id;
        }

        return -1;
    }

    public int getNativeClassId(String className) {
        // search through all native classes
        for (int i = 0; i < nativeClasses.size(); i++) {
            NativeClass nativeClass = nativeClasses.elementAt(i);
            if (nativeClass.className.equals(className))
                return nativeClass.id;
        }
        return -1;
    }

    private NativeClass loadAnnotatedNativeClass(String className) {
        try {
            String filePath = className.replace('.', '/')+".class";
            byte[] nativeData = loadResource(classPath, filePath);

            ClassPool cp = new ClassPool();
            CtClass ctClass = cp.makeClass(new ByteArrayInputStream(nativeData));
            Tracer.debug("Found class "+ctClass.getName());

            Native nativeAnnotation = (Native)ctClass.getAnnotation(Native.class);
            if(nativeAnnotation == null){
                return null;
            }
            Tracer.debug("Class has native ID "+nativeAnnotation.id());

            NativeClass res = new NativeClass();
            res.className = ctClass.getName().replace('.', '/');
            res.id = nativeAnnotation.id();
            Tracer.debug("Found "+res);
            nativeClasses.add(res);

            // c'tors
            for(CtConstructor ctC : ctClass.getConstructors()){
                nativeAnnotation = (Native)ctC.getAnnotation(Native.class);
                if(nativeAnnotation == null){
                    continue;
                }
                NativeMethod nativeMethod = new NativeMethod();
                nativeMethod.className = res.className;
                nativeMethod.name = "<init>";
                nativeMethod.id = nativeAnnotation.id() + (res.id << 8);
                nativeMethod.type = ctC.getParameterTypes().length == 0 ? "()V" : "FIXME";
                Tracer.debug("Found "+nativeMethod);
                nativeMethods.add(nativeMethod);
            }

            // apply methods
            for(CtMethod ctMethod : ctClass.getMethods()){
                nativeAnnotation = (Native)ctMethod.getAnnotation(Native.class);
                if(nativeAnnotation == null){
                    continue;
                }
                NativeMethod nativeMethod = new NativeMethod();
                nativeMethod.className = res.className;
                nativeMethod.name = ctMethod.getName();
                nativeMethod.id = nativeAnnotation.id() + (res.id << 8);
                nativeMethod.type = ctMethod.getReturnType().getName();
                Tracer.debug("Found "+nativeMethod);
                nativeMethods.add(nativeMethod);
            }

            if (res.id < lowestNativeId)
                                   lowestNativeId = res.id;

            return res;

        } catch(Exception ex){
            ex.printStackTrace();
        }
        return null;
    }

    private NativeClass loadNativeClass(String className) throws ClassNotFoundException {
        System.out.println("read native " + className);
        Tracer.debug("read native "+ className);


        NativeClass res = null;
        // try annotations
        res = loadAnnotatedNativeClass(className);
        if(res != null){
            return res;
        }

        String filePath = className.replace('.', '/')+".native";
        byte[] nativeData = loadResource(classPath, filePath);
        if(nativeData == null){
            return null;
        }

        try {
            String line;
            String fullClassName = null;
            int fullClassId = 0;
            BufferedReader reader = new BufferedReader(new InputStreamReader(new ByteArrayInputStream(nativeData)));


            // read through all lines in file
            while ((line = reader.readLine()) != null) {
                StringTokenizer st = new StringTokenizer(line);
                boolean skipRest = false;
                int token_cnt = 0;
                String name = null, value = null, id = null;

                while (st.hasMoreTokens() && !skipRest) {
                    String token = st.nextToken();

                    if (token.charAt(0) == '#')
                        skipRest = true;
                    else {

                        if (token_cnt == 0) name = token;
                        else if (token_cnt == 1) value = token;
                        else if (token_cnt == 2) id = token;
                        else {
                            System.out.println("Ignoring superfluous data: " + token);
                        }

                        token_cnt++;
                    }
                }

                if (token_cnt > 0) {
                    // class entry
                    if (name.equalsIgnoreCase("class") && (token_cnt == 3)) {
                        res = new NativeClass();
                        res.className = value;
                        res.id = Integer.parseInt(id);
                        Tracer.debug("Found "+res);
                        nativeClasses.addElement(res);

                        if (Integer.parseInt(id) < lowestNativeId)
                            lowestNativeId = Integer.parseInt(id);

                        // save locally for further method processing
                        fullClassName = value;
                        fullClassId = Integer.parseInt(id);
                    }
                    // method entry
                    else if (name.equalsIgnoreCase("method") && (token_cnt == 3)) {
                        if (value.indexOf(':') == -1) {
                            System.out.println("Invalid method reference");
                            System.exit(-1);
                        }

                        if (fullClassName == null) {
                            System.out.println("Method reference before class");
                            System.exit(-1);
                        }

                        // seperate class, method and type
                        NativeMethod nativeMethod = new NativeMethod();
                        nativeMethod.className = fullClassName;
                        nativeMethod.name = value.substring(0, value.indexOf(':'));
                        nativeMethod.type = value.substring(
                                value.indexOf(':') + 1, value.length());
                        nativeMethod.id = Integer.parseInt(id) + (fullClassId << 8);
Tracer.debug("Found "+nativeMethod);
                        nativeMethods.addElement(nativeMethod);
                    }

                    // field entry
                    else if (name.equalsIgnoreCase("field") && (token_cnt == 3)) {
                        if (value.indexOf(':') == -1) {
                            System.out.println("Invalid field reference");
                            System.exit(-1);
                        }

                        if (fullClassName == null) {
                            System.out.println("Method reference before class");
                            System.exit(-1);
                        }

                        // seperate class, method and type
                        NativeField nativeField = new NativeField();
                        nativeField.className = fullClassName;
                        nativeField.name = value.substring(0, value.indexOf(':'));
                        nativeField.type = value.substring(
                                value.indexOf(':') + 1, value.length());
                        nativeField.id = Integer.parseInt(id) + (fullClassId << 8);

                        nativeFields.addElement(nativeField);
                    } else {
                        System.out.println("Unknown entry in native file: " + name +
                                " + " + token_cnt + " parms");
                        System.exit(-1);
                    }
                }
            }
        } catch (IOException e) {
            System.out.println(e.toString());
            throw new ClassNotFoundException("Error at native reading "+className, e);
        }
        if(res == null){
            throw new ClassNotFoundException("Native class not found "+className);
        }
        return res;
    }


}

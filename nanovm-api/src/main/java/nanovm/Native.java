package nanovm;

import java.lang.annotation.*;

@Retention(RetentionPolicy.RUNTIME)
public @interface Native {
    public int id();
}

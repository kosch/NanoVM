package org.nanovm.converter;

//
//  NanoVMTool, Converter and Upload Tool for the NanoVM
//  Copyright (C) 2005 by Till Harbaum <Till@Harbaum.org>
//
//  This program is free software; you can redistribute it and/or modify
//  it under the terms of the GNU General Public License as published by
//  the Free Software Foundation; either version 2 of the License, or
//  (at your option) any later version.
//
//  This program is distributed in the hope that it will be useful,
//  but WITHOUT ANY WARRANTY; without even the implied warranty of
//  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
//  GNU General Public License for more details.
//
//  You should have received a copy of the GNU General Public License
//  along with this program; if not, write to the Free Software
//  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
//
//  Parts of this tool are based on public domain code written by Kimberley
//  Burchett: http://www.kimbly.com/code/classfile/
//

/**
 * Bitfield constants for class/field/method access flags.
 */
public interface AccessFlags {
    short PUBLIC = 0x0001;
    short PRIVATE = 0x0002;
    short PROTECTED = 0x0004;
    short STATIC = 0x0008;
    short FINAL = 0x0010;
    short SYNCHRONIZED = 0x0020;
    short VOLATILE = 0x0040;
    short TRANSIENT = 0x0080;
    short NATIVE = 0x0100;
    short INTERFACE = 0x0200;
    short ABSTRACT = 0x0400;
}

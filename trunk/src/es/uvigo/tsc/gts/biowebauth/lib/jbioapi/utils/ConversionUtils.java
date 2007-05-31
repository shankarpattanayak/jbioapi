/* BioWebAuth (Biometrics for Web Authentication) is an open-source Java 
 * framework intended to provide web authentication based on BioAPI-compliant 
 * biometric software or devices.
 * 
 * Copyright (c) 2005-2007 Elisardo Gonzalez Agulla <eli@gts.tsc.uvigo.es> 
 *  		          & Enrique Otero Muras <eotero@gts.tsc.uvigo.es>
 *
 * This library is free software; you can redistribute it and/or
 * modify it under the terms of the GNU Lesser General Public
 * License as published by the Free Software Foundation; either
 * version 2.1 of the License, or (at your option) any later version.
 *
 * This library is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * Lesser General Public License for more details.
 *
 * You should have received a copy of the GNU Lesser General Public
 * License along with this library; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA  02110-1301  USA
 */

/*
 * ConversionUtils.java
 *
 * Created on 19 de diciembre de 2005, 12:03
 */

package es.uvigo.tsc.gts.biowebauth.lib.jbioapi.utils;

/**
 *
 * @author eli
 */
public class ConversionUtils {
    
    /** Creates a new instance of ConversionUtils */
    private ConversionUtils() {
    }
    
    
    
    public static byte[] int2ByteArrayLength4( int theInt ) {
        byte[] byteLong = new byte[4];
        byteLong[0] = (byte)( ( theInt >>> 24 )&0xff  );
        byteLong[1] = (byte)( ( theInt >>> 16 )&0xff  );
        byteLong[2] = (byte)( ( theInt >>> 8  )&0xff  );
        byteLong[3] = (byte)( ( theInt )&0xff  );
        return byteLong;
    }
    
     public static byte[] int2ByteArrayLength2( int theInt ) {
        byte[] byteInt = new byte[2];
        byteInt[0] = (byte)( ( theInt >>> 8  )&0xff  );
        byteInt[1] = (byte)( ( theInt )&0xff  );
        return byteInt;
    }
    
    public static byte short2Byte( short theInt ) {
        byte[] byteShort = new byte[1];
        byteShort[0] = (byte)( ( theInt )&0xff  );
        return byteShort[0];
    }
    
    public static byte[] long2ByteArray( long srcValue, int len )  throws IllegalArgumentException {
        
        if( len != 2 && len != 4 && len != 6 && len != 8 )
            throw new IllegalArgumentException( "illegal length: " + len );
        
        byte[] tempBytes = new byte[len];
        
        for( int i = 0; i < len; i++ ) {
            long tempValue = srcValue;
            tempValue >>= 8 * i;
            // tempBytes[len-i-1] = (byte)(tempValue & 0xFF);
            tempBytes[i] = (byte)(tempValue & 0xFF);
        }
        
        return tempBytes;
    }
    
    public static long byte2Long( int loc, byte b[] ) {
        int shift;
        long kk, jj = 0;
        shift = 0;
        for (int i=0; i<8; i++) {
            kk = (long)(b[loc+i]); if (kk<0) kk=256+kk;
            kk = (kk << shift);
            jj = jj + kk;
            shift = shift + 8;
        }
        return jj;
    }
    
    public static short byte2Short( int loc, byte b[] ) {
        short m1, m2;
        m1 = (short)(b[loc]); if (m1<0) m1=(short)(256+m1);
        m2 = (short)(b[loc+1]); if (m2<0) m2=(short)(256+m2);
        m2 = (short)(256*m2 + m1);
        return m2;
    }
    
    
    
    
    
    
    
    public static byte Str2Byte(String i) {
        if ( i.indexOf(".") >= 0 ) { int p = i.indexOf(".") ; i = i.substring(0,p) ;}
        
        byte o ;
        try { o = Byte.parseByte(i) ;} catch (Exception e) { o = 0 ;}
        return o ;
    }
    
    public static double Str2Double(String i) {
        double o ;
        try { o = Double.parseDouble(i) ;} catch (Exception e) { o = 0 ;}
        return o ;
    }
    
    public static float Str2Float(String i) {
        float o ;
        try { o = Float.parseFloat(i) ;} catch (Exception e) { o = 0 ;}
        return o ;
    }
    
    public static int Str2Int(String i) {
        if ( i.indexOf(".") >= 0 ) { int p = i.indexOf(".") ; i = i.substring(0,p) ;}
        
        int o ;
        try { o = Integer.parseInt(i) ;} catch (Exception e) { o = 0 ;}
        return o ;
    }
    
    public static long Str2Long(String i) {
        if ( i.indexOf(".") >= 0 ) { int p = i.indexOf(".") ; i = i.substring(0,p) ;}
        
        long o ;
        try { o = Long.parseLong(i) ;} catch (Exception e) { o = 0 ;}
        return o ;
    }
    
    public static short Str2Short(String i) {
        if ( i.indexOf(".") >= 0 ) { int p = i.indexOf(".") ; i = i.substring(0,p) ;}
        
        short o ;
        try { o = Short.parseShort(i) ;} catch (Exception e) { o = 0 ;}
        return o ;
    }
    
    public static String Byte2Str(byte i) {
        String o ;
        try { o = Byte.toString(i) ;} catch (Exception e) { o = "" ;}
        return o ;
    }
    
    public static double Byte2Double(byte i) {
        double o ;
        try { o = (double)i ;} catch (Exception e) { o = 0 ;}
        return o ;
    }
    
    public static float Byte2Float(byte i) {
        float o ;
        try { o = (float)i ;} catch (Exception e) { o = 0 ;}
        return o ;
    }
    
    public static int Byte2Int(byte i) {
        int o ;
        try { o = (int)i ;} catch (Exception e) { o = 0 ;}
        return o ;
    }
    
    public static long Byte2Long(byte i) {
        long o ;
        try { o = (long)i ;} catch (Exception e) { o = 0 ;}
        return o ;
    }
    
    public static short Byte2Short(byte i) {
        short o ;
        try { o = (short)i ;} catch (Exception e) { o = 0 ;}
        return o ;
    }
    
    public static String Double2Str(double i) {
        String o ;
        try { o = Double.toString(i) ;} catch (Exception e) { o = "" ;}
        
        if ( o.indexOf(".0") == (o.length()-2) ) { o = o.substring(0, (o.length()-2) ) ;}
        return o ;
    }
    
    public static byte Double2Byte(double i) {
        byte o ;
        try { o = new Double(i).byteValue() ;} catch (Exception e) { o = 0 ;}
        return o ;
    }
    
    public static float Double2Float(double i) {
        float o ;
        try { o = new Double(i).floatValue() ;} catch (Exception e) { o = 0 ;}
        return o ;
    }
    
    public static int Double2Int(double i) {
        int o ;
        try { o = new Double(i).intValue() ;} catch (Exception e) { o = 0 ;}
        return o ;
    }
    
    public static long Double2Long(double i) {
        long o ;
        try { o = new Double(i).longValue() ;} catch (Exception e) { o = 0 ;}
        return o ;
    }
    
    public static short Double2Short(double i) {
        short o ;
        try { o = new Double(i).shortValue() ;} catch (Exception e) { o = 0 ;}
        return o ;
    }
    
    public static String Float2Str(float i) {
        String o ;
        try { o = Float.toString(i) ;} catch (Exception e) { o = "" ;}
        
        if ( o.indexOf(".0") == (o.length()-2) ) { o = o.substring(0, (o.length()-2) ) ;}
        return o ;
    }
    
    public static byte Float2Byte(float i) {
        byte o ;
        try { o = new Float(i).byteValue() ;} catch (Exception e) { o = 0 ;}
        return o ;
    }
    
    public static double Float2Double(float i) {
        double o ;
        try { o = (double)i ;} catch (Exception e) { o = 0 ;}
        return o ;
    }
    
    public static int Float2Int(float i) {
        int o ;
        try { o = new Float(i).intValue() ;} catch (Exception e) { o = 0 ;}
        return o ;
    }
    
    public static long Float2Long(float i) {
        long o ;
        try { o = new Float(i).longValue() ;} catch (Exception e) { o = 0 ;}
        return o ;
    }
    
    public static short Float2Short(float i) {
        short o ;
        try { o = new Float(i).shortValue() ;} catch (Exception e) { o = 0 ;}
        return o ;
    }
    
    public static String Int2Str(int i) {
        String o ;
        try { o = Integer.toString(i) ;} catch (Exception e) { o = "" ;}
        return o ;
    }
    
    public static byte Int2Byte(int i) {
        byte o ;
        try { o = new Integer(i).byteValue() ;} catch (Exception e) { o = 0 ;}
        return o ;
    }
    
    
    public static double Int2Double(int i) {
        double o ;
        try { o = (double)i ;} catch (Exception e) { o = 0 ;}
        return o ;
    }
    
    public static float Int2Float(int i) {
        float o ;
        try { o = (float)i ;} catch (Exception e) { o = 0 ;}
        return o ;
    }
    
    public static long Int2Long(int i) {
        long o ;
        try { o = (long)i ;} catch (Exception e) { o = 0 ;}
        return o ;
    }
    
    public static short Int2Short(int i) {
        short o ;
        try { o = new Integer(i).shortValue() ;} catch (Exception e) { o = 0 ;}
        return o ;
    }
    
    public static String Long2Str(long i) {
        String o ;
        try { o = Long.toString(i) ;} catch (Exception e) { o = "" ;}
        return o ;
    }
    
    public static byte Long2Byte(long i) {
        byte o ;
        try { o = new Long(i).byteValue() ;} catch (Exception e) { o = 0 ;}
        return o ;
    }
    
    public static double Long2Double(long i) {
        double o ;
        try { o = (double)i ;} catch (Exception e) { o = 0 ;}
        return o ;
    }
    
    public static float Long2Float(long i) {
        float o ;
        try { o = (float)i ;} catch (Exception e) { o = 0 ;}
        return o ;
    }
    
    public static int Long2Int(long i) {
        int o ;
        try { o = new Long(i).intValue() ;} catch (Exception e) { o = 0 ;}
        return o ;
    }
    
    public static short Long2Short(long i) {
        short o ;
        try { o = new Long(i).shortValue() ;} catch (Exception e) { o = 0 ;}
        return o ;
    }
    
    public static String Short2Str(short i) {
        String o ;
        try { o = Short.toString(i) ;} catch (Exception e) { o = "" ;}
        return o ;
    }
    
    public static byte Short2Byte(short i) {
        byte o ;
        try { o = new Short(i).byteValue() ;} catch (Exception e) { o = 0 ;}
        return o ;
    }
    
    public static double Short2Double(short i) {
        double o ;
        try { o = (double)i ;} catch (Exception e) { o = 0 ;}
        return o ;
    }
    
    public static float Short2Float(short i) {
        float o ;
        try { o = (float)i ;} catch (Exception e) { o = 0 ;}
        return o ;
    }
    
    public static int Short2Int(short i) {
        int o ;
        try { o = (int)i ;} catch (Exception e) { o = 0 ;}
        return o ;
    }
    
    public static long Short2Long(short i) {
        long o ;
        try { o = (long)i ;} catch (Exception e) { o = 0 ;}
        return o ;
    }
    

}

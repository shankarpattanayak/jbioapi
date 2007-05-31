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

package es.uvigo.tsc.gts.biowebauth.lib.jbioapi.utils;


public class BioAPI_BIR_HEADER_Customize {
    
    
    private byte[] header;
    
    public BioAPI_BIR_HEADER_Customize(int formatOwner, int formatID, short purpose) {
        header= new byte[16];
        //Length
        header[0]=0x00;
        header[1]=0x00;
        header[2]=0x00;
        header[3]=0x00;
        // Header Version
        header[4]=0x01;
        // BIR data Type
        header[5]=0x01; // RAW
        
        // Format
        // ---> Owner
        header[6]=0x00;
        header[7]=0x00;
        byte[] fOwner =ConversionUtils.int2ByteArrayLength2(formatOwner);
        header[6]=fOwner[1];
        header[7]=fOwner[0];
        // ---> ID
        header[8]=0x00;
        header[9]=0x00;
        byte[] fID =ConversionUtils.int2ByteArrayLength2(formatID);
        header[8]=fID[1];
        header[9]=fID[0];
        
        // Quality
        header[10]='d';
        // Purpose Mask
        header[11]= ConversionUtils.short2Byte(purpose);
        // Factors Mask
        header[12]=0x00;
        header[13]=0x00;
        header[14]=0x00;
        header[15]=0x00;
    }
    
    
    public void setPacketLength(long length) {
        byte[] b = new byte[4];
        
        b= ConversionUtils.long2ByteArray(length, 4);
        System.arraycopy(b, 0, header, 0, 4);
    }
    
    
    public long getPacketLength() {
        byte[] b = new byte[4];
        
        System.arraycopy(header, 0, b, 0, 4);
        
        return ConversionUtils.byte2Long(0,b);
    }
    
    
    
    public byte[] getBirHeader(){
        return header;
    }
    
    
    
}

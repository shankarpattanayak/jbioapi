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
 * BIRHelper.java
 *
 * Created on 19 de diciembre de 2005, 10:45
 */

package es.uvigo.tsc.gts.biowebauth.lib.jbioapi.utils;

import es.uvigo.tsc.gts.biowebauth.lib.model.vo.FileVO;
import es.uvigo.tsc.gts.biowebauth.lib.model.vo.SampleVO;
import java.util.ArrayList;
import java.util.Iterator;

/**
 *
 * @author eli
 */
public class BIRHelper {
    public static int FORMAT_ID_SIMPLE_BIR_UNKNOWN=0;
    public static int FORMAT_ID_SIMPLE_AUDIO_BIR=1;
    public static int FORMAT_ID_SIMPLE_VIDEO_BIR=2;
    public static int FORMAT_ID_SIMPLE_IMAGE_BIR=3;
    public static int FORMAT_ID_SIMPLE_MUTE_VIDEO_BIR=4;
    public static int FORMAT_ID_COMPOSED_BIR=6;
    
    public static int FORMAT_OWNER_COMPOSED_BIR=0;
    
    public static byte[] createSimpleBIRFromRawSampleVO(SampleVO sample,int formatOwner, int formatID, short purpose) throws Exception{
        if (sample==null) throw new Exception("SampleVO is null");
        if (sample.getFile()==null) throw new Exception("SampleVO getFile return a null value.");
        
        
        FileVO f = sample.getFile();
        return createSimpleBIR(f.getContent(), formatOwner, formatID, purpose);
    }
    
    public static byte[] createComposedBIRFromArrayOfRawSampleVO(SampleVO[] samples,int formatOwner, int formatID, short purpose) throws Exception{
        if (samples==null) throw new Exception("Array of SampleVOs is null");
        if (samples.length==1) {
            return createSimpleBIR(samples[0].getFile().getContent(), formatOwner, formatID, purpose);
        }
        
        int numberOfSamples= samples.length;
        
        // List of SimpleBIRs
        ArrayList simpleBirs= new ArrayList(numberOfSamples);
        for (int i=0;i<numberOfSamples;i++){
            byte[] simpleBir=createSimpleBIR(samples[i].getFile().getContent(), formatOwner, formatID, purpose);
            simpleBirs.add(simpleBir);
        }
        return createComposedBIR(simpleBirs, formatOwner, formatID, purpose);
        
    }
    public static byte[] createComposedBIRFromArrayOfSampleVO(SampleVO[] samples) throws Exception{
        if (samples==null) throw new Exception("Array of SampleVOs is null");
        else if (samples.length==1) {
            return samples[0].getFile().getContent();
        }
        
        int numberOfSamples= samples.length;
        short purpose = 0 ;
        
        // List of SimpleBIRs
        ArrayList simpleBirs= new ArrayList(numberOfSamples);
        for (int i=0;i<numberOfSamples;i++){
            
            byte[] simpleBir=samples[i].getFile().getContent();
            purpose=ConversionUtils.Byte2Short(simpleBir[11]);
            simpleBirs.add(simpleBir);
        }
        return createComposedBIR(simpleBirs,FORMAT_OWNER_COMPOSED_BIR, FORMAT_ID_COMPOSED_BIR, purpose);
        
    }
    
    private static byte[] createSimpleBIR(byte[] rawContent,int formatOwner, int formatID, short purpose){
        
        int rawContentLength= rawContent.length;
        BioAPI_BIR_HEADER_Customize head = new BioAPI_BIR_HEADER_Customize(formatOwner,formatID,purpose);
        head.setPacketLength(rawContentLength+16);
       
        
        byte[] bir= new byte[16+rawContentLength];
        
        System.arraycopy(head.getBirHeader(),0, bir, 0, 16);
        System.arraycopy(rawContent,0, bir, 16, rawContentLength);
        
        return bir;
    }
    
    
    private static byte[] createComposedBIR(ArrayList simpleBirs,int formatOwner, int formatID, short purpose){
        byte[] composedBir;
        byte[] bodyBir;
        byte[] tmpBuffer;
        
        // Number of BIRs
        bodyBir= ConversionUtils.int2ByteArrayLength4(simpleBirs.size());
        
        BioAPI_BIR_HEADER_Customize head = new BioAPI_BIR_HEADER_Customize(formatOwner,formatID,purpose);
        
        Iterator simpleBirsIter = simpleBirs.iterator();
        
        while (simpleBirsIter.hasNext()){
            byte[] bir = (byte[]) simpleBirsIter.next();
            int lengthBir = bir.length;
            byte[] dataLength =  ConversionUtils.int2ByteArrayLength4(lengthBir);
            
            tmpBuffer = new byte[bodyBir.length + dataLength.length + bir.length];
            // Copy the previous BIRs
            System.arraycopy(bodyBir, 0, tmpBuffer,0, bodyBir.length);
            
            // long of the new bir
            System.arraycopy(dataLength, 0, tmpBuffer, bodyBir.length, dataLength.length);
            // add new bir data
            System.arraycopy(bir, 0, tmpBuffer, bodyBir.length+ dataLength.length, bir.length);
            
            // Update the body bir;
            bodyBir= tmpBuffer;
            
        }
        
        composedBir = new byte[16+bodyBir.length];
        
        
        head.setPacketLength(bodyBir.length+16);
        System.arraycopy(head.getBirHeader(),0, composedBir, 0, 16);
        System.arraycopy(bodyBir,0, composedBir, 16, bodyBir.length);
        
        return composedBir;
    }
    
    
    
    
}

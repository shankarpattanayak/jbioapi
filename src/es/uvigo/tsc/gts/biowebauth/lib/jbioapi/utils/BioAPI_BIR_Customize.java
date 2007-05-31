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
 * BioAPI_BIR_Customize.java
 *
 * Created on 19 de diciembre de 2005, 17:04
 */

package es.uvigo.tsc.gts.biowebauth.lib.jbioapi.utils;

/**
 *
 * @author eli
 */
public class BioAPI_BIR_Customize {
    public byte[] bir;
    /** Creates a new instance of BioAPI_BIR_Customize */
    public BioAPI_BIR_Customize(byte[] bir) {
        this.bir=bir;
    }
    
    
    public byte getPurpose(){
        return  bir[11];
    }
    
}

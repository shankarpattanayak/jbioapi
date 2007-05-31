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
 * FileVO.java
 *
 * Created on 17 de marzo de 2005, 15:30
 */

package es.uvigo.tsc.gts.biowebauth.lib.model.vo;

import java.io.Serializable;

/**
 *
 * @author eli
 */
public class FileVO implements Serializable  {
    String name;
    byte[] content;
    
     public FileVO() {
         super();
    }
    
    
    /** Creates a new instance of FileVO */
    public FileVO(String name,byte[] content) {
        this();
        this.name=name;
        this.content=content;
    }
    
    
    public void setName(String name){
        this.name=name;
    }
    
    public String getName(){
        return this.name;
    }
    
    public void setContent(byte[] content){
        this.content=content;
    }
    
    public byte[] getContent(){
        return this.content;
    }
    
}

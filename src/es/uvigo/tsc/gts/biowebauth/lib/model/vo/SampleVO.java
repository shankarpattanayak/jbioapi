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
 * SampleVO.java
 *
 * Created on 17 de marzo de 2005, 15:25
 */

package es.uvigo.tsc.gts.biowebauth.lib.model.vo;

import java.io.Serializable;

/**
 *
 * @author eli
 */
public class SampleVO implements Serializable {
    private String type;
    private String name;
    private String description;
    private FileVO file;
    
    /** Creates a new instance of SampleVO */
    public SampleVO() {
        super();
    }
        
     public String getName() {
        return name;
    }
    
    public void setName(String name) {
        this.name = name;
    }
    
    public String getDescription() {
        return description;
    }
    
    public void setDescription(String description) {
        this.description = description;
    }
    public void setType(String type) {
        this.type = type;
    }
    
    public String getType() {
        return this.type;
    }
    
    public void setFile(FileVO file){
        this.file = file;
    }
    
    public FileVO getFile(){
        return this.file;
    }
    
}

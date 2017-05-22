<?php

/**
 * Created by PhpStorm.
 * User: itcyb
 * Date: 5/22/2017
 * Time: 9:53 PM
 */
class Upload
{
    protected $type;

    protected $name;

    protected $tmp_file;

    protected $file;

    protected $size;

    protected $errors;

    protected $msg;

    protected $directory;

    protected $ext;

    protected $allowed;

    /**
     * Upload constructor.
     */
    public function __construct()
    {
        $this->type=null;
        $this->name=null;
        $this->tmp_file=null;
        $this->file=null;
        $this->size=0;
        $this->errors=false;
        $this->directory=$_SERVER['DOCUMENT_ROOT']."/uploads/";
        $this->ext=null;
        $this->allowed=array();
    }

    public function setAll(){
        #set tmp_file
        if($this->file!==null && $this->file!=="") {
            $this->tmp_file=$this->file['tmp_name'];
            #set name
            if($this->name!=="" && $this->name!==null){
                $this->ext=pathinfo($this->file['name'],PATHINFO_EXTENSION);
                $this->name=$this->name.".".$this->ext;
            }else{
                $this->name=$this->file['name'];
            }
            #set size,type,ext
            if ($this->tmp_file !== "" && $this->tmp_file !== null) {
                $this->size = filesize($this->tmp_file);
                $this->type = mime_content_type($this->tmp_file);
            } else {
                #throw error
            }

            #check directory
            if(!file_exists($this->directory)){
                mkdir($this->directory);
            }else{

            }
        }
    }

    public function up()
    {
        if(move_uploaded_file($this->tmp_file, $this->directory.$this->name)){
            $this->msg="success";
        }else{
            $this->msg="Failed";
        }
    }


    /**
     * setters
     */
    /**
     * @param null $name
     */
    public function setName($name)
    {
        $this->name = $name;
    }

    /**
     * @param null $file
     */
    public function setFile($file)
    {
        $this->file = $file;
    }

    /**
     * getters
     */

    /**
     * @return null
     */
    public function getType()
    {
        return $this->type;
    }

    /**
     * @return int
     */
    public function getSize(): int
    {
        return $this->size;
    }

    /**
     * @return bool
     */
    public function isErrors(): bool
    {
        return $this->errors;
    }

    /**
     * @return mixed
     */
    public function getMsg()
    {
        return $this->msg;
    }

    /**
     * @return null
     */
    public function getExt()
    {
        return $this->ext;
    }
}

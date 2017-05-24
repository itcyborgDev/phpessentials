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

    protected $maxSize;

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
        $this->maxSize = 0;
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
                $this->ext = pathinfo($this->file['name'], PATHINFO_EXTENSION);
                $this->name=$this->file['name'];
            }
            #set size,type,ext
            if ($this->tmp_file !== "" && $this->tmp_file !== null) {
                $this->size = filesize($this->tmp_file);
                $this->type = mime_content_type($this->tmp_file);

            } else {
                #throw error
                $this->errors = true;
                $this->msg = "An error has occured";
            }

            #check size
            if ($this->maxSize !== 0) {
                if ($this->maxSize < $this->size) {
                    $this->errors = true;
                    $this->msg = "File too big. Maximum file size allowed is " . $this->maxSize;
                    throw new UploadException($this->msg);
                }
            }

            #check directory
            if(!file_exists($this->directory)){
                if (mkdir($this->directory)) {
                    $this->errors = false;
                    $this->msg = "Directory has been created successfully";
                } else {
                    $this->errors = true;
                    $this->msg = "Failed to create directory";
                }
            } else {
                $this->msg = "Directory found";
            }

            #check if allowed
            if (in_array($this->type, $this->allowed) || in_array($this->ext, $this->allowed)) {
                $this->errors = false;
            } else {
                $this->errors = true;
                throw new UploadException("Not allowed");
            }
        } else {
            $this->errors = true;
            $this->msg = "No file has been selected for upload";
            throw new UploadException($this->msg);
        }
    }

    public function up()
    {
        if(move_uploaded_file($this->tmp_file, $this->directory.$this->name)){
            $this->msg="success";
            $this->errors = false;
        }else{
            $this->msg="Failed";
            $this->errors = true;
            throw new UploadException($this->msg);
        }
    }


    /**
     * setters
     */
    /**
     * @param mixed $maxSize
     */
    public function setMaxSize($maxSize)
    {
        $this->maxSize = $maxSize;
    }

    /**
     * @param null $file
     */
    public function setFile($file)
    {
        $this->file = $file;
    }

    /**
     * @param string $directory
     */
    public function setDirectory(string $directory)
    {
        $this->directory = $directory;
    }

    /**
     * @param array $allowed
     */
    public function setAllowed(array $allowed)
    {
        $this->allowed = $allowed;
    }

    /**
     * @return null
     */
    public function getType()
    {
        return $this->type;
    }

    /**
     * getters
     */

    public function getName()
    {
        return $this->name;
    }

    /**
     * @param null $name
     */
    public function setName($name)
    {
        $this->name = $name;
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

class UploadException extends Exception
{

}
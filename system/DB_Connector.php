<?php

/**
 * Created by PhpStorm.
 * User: itcyb
 * Date: 5/7/2017
 * Time: 8:18 AM
 */
class DB_Connector
{
    /**
     * @var PDO
     */
    private $connection;

    /**
     * @var
     */
    private $query;

    /**
     * @var
     */
    private $dbhost;

    /**
     * @var
     */
    private $dbname;

    /**
     * @var
     */
    private $dbuser;

    /**
     * @var
     */
    private $dbpass;

    /**
     * @var
     */
    private $type;

    /**
     * @var
     */
    private $errors;

    /**
     * DB_Connector constructor.
     */
    public function __construct()
    {
        /**
         *  [0]  ->  dbhost,
         *  [1]  ->  dbname,
         *  [2]  ->  dbuser,
         *  [3]  ->  dbpass,
         *  [4]  ->  type
         */

        $_details=fopen('../config/config.ini','r');
        $_details=fread($_details,filesize('../config/config.ini'));
        if($_details==="" || $_details===null) {

        }else{
            $_detail = explode("|", $_details);
            /*$this->"";
            $this$_detail[0]);
            $this->setDbname($_detail[1]);
            $this->setDbuser($_detail[2]);
            $this->setDbpass($_detail[3]);
            $this->setType($_detail[4]);
            try {
                $this->connection = new PDO("mysql:host=$this->dbhost;dbname=$this->dbname", $this->dbuser, $this->dbpass, array(PDO::ATTR_EMULATE_PREPARES => true, PDO::ATTR_ERRMODE => PDO::ERRMODE_EXCEPTION, INFO_GENERAL));
            }catch (PDOException $e){
                throw new DB_ConnectorException($e);
            }*/
        }
    }

    /**
     * @return mixed
     */
    public function connectionDetails(){
        return $this->connection->getAttribute(PDO::ATTR_SERVER_INFO);
    }

    /**
     * @param null $table
     * @param null $attributes
     */
    private function put($table, $attributes){
        return $this->queryConstruct($table,1,$attributes);
    }

    /**
     * @param null $table
     * @param null $attributes
     */
    private function update($table, $attributes){
        return $this->queryConstruct($table,3,$attributes);
    }

    /**
     * @param null $table
     * @param null $attributes
     */
    private function get($table, $attributes){
        $this->queryConstruct($table,2,$attributes);
    }

    /**
     * @param $type
     * @param null $array
     */
    protected function queryConstruct($table,$type, $array){
        $construct = "";
        if($type==2) {
            if (is_array($array)) {
                $attributes = $array;
                foreach ($attributes as $attribute => $value) {
                    if ($attribute != null || $value != null) {
                        if ($construct == "") {
                            $construct = "UPDATE $table SET $attribute='$value'";
                        } else {
                            $construct .= ",SET $attribute='$value'";
                        }
                    }
                }
            } else {
                throw new DB_ConnectorException("Error. Array required with 'column' => 'value' format.", 002);
            }
        }elseif ($type==1){
            $columns="";
            $values="";
            if(is_array($array)){
                $attributes=$array;
                foreach ($attributes as $attribute=>$value) {
                    if ($attribute != null || $value != null) {
                        if($columns==""){
                            $columns="$attribute";
                        }else{
                            $columns.=",$attribute";
                        }
                        if($values==""){
                            $values="'$value'";
                        }else{
                            $values.=",'$value'";
                        }
                    }
                }
                $construct="INSERT INTO $table($columns) VALUES ($values)";
            }
        }
        return $construct;
    }

    /**
     * @param $table
     * @param $attributes
     * @param $type
     */
    public function dbquery($table, $attributes, $type){
        $return=null;
        if($type=="I" || $type=="i"){
            $return= $this->put($table,$attributes);
        }elseif($type=="S" || $type=="s"){
            $return =$this->get($table,$attributes);
        }elseif($type=="U" || $type=="u"){
            $return =$this->update($table,$attributes);
        }else{
            throw new DB_ConnectorException("Unregistered type of query. Please refer to the help docs for the list of supported commands.",001);
        }
        return $return;
    }
}

/**
 * Class DB_ConnectorException
 */
class DB_ConnectorException extends Exception {

}
$db=new DB_Connector();
$attr=array(
    'id'=>1,
    'name'=>'isaac',
    'type'=>'admin',
    'age'=>20
);
echo $db->dbquery("users",$attr,"I");
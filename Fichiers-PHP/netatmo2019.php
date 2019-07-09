<?php
/**
* Example of Netatmo Welcome API
* For further information, please take a look at https://dev.netatmo.com/doc
*/

// *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
// *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*      DEBUG      *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
$debug = FALSE;

// Petite fonction pour afficher avec des retours les tableaux lors d'un debug
function print_r2($val){
        echo '<pre>';
        print_r($val);
        echo  '</pre>';
}
// *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*    FIN DEBUG    *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*


// On défini ici la variable du chemi absolu de là où se trouve le script php
// Sur mon synology, la fonction dirname(dirname(__FILE__)) donnait que /VolumeX
// alors que le fichier php était dans /VolumeX/web/ , donc j'ajoute /web/ après le résultat de dirname(dirname(__FILE__))
define('__ROOT__', dirname(dirname(__FILE__)) . '/web/');
	
// On définit ici les variables de chemin d'accès aux trois fichiers nécessaires à inclure
// Il faudra avoir placé les fichiers dans le dossier src (fourni par Netatmo)
define('_configpath_', __ROOT__ . 'src/Config.php');
define('_utilpath_', __ROOT__ . 'src/Utils.php');
define('_autoloadpath_', __ROOT__ . 'src/Netatmo/autoload.php');

// On inclue (PHP vérifie si le fichier a déjà été inclus, et si c'est le cas, ne l'inclut
// pas une deuxième fois) et exécute les fichiers précédents.
// Et avec require_once lorsqu'une erreur // survient, le script est arrêté, et plus rien
// ne se passe ensuite. 
require_once (_autoloadpath_);
require_once (_configpath_);
require_once (_utilpath_);

/**
 * Prints a list of devices
 * Les autres fonctions printxxxxxx sont dans Utils.php
 * Ne sert pas vraiment dans le script utilisé pour générer les données pour l'Arduino.
 * Mais en cas de DEBUG, ça peut servir.
 */
function printDevices($devices, $title = NULL)
{
    if(!is_null($devices) && is_array($devices) && !empty($devices))
    {
        if(!is_null($title))
            printMessageWithBorder($title);

        foreach($devices as $device)
        {
            printWSBasicInfo($device);
        }
    }
}

//App client configuration
$scope = Netatmo\Common\NAScopes::SCOPE_READ_STATION;
$config = array("client_id" => $client_id,
                "client_secret" => $client_secret,
                "username" => $test_username,
                "password" => $test_password);

$client = new Netatmo\Clients\NAWSApiClient($config);

//Authentication with Netatmo server (OAuth2)
try
{
    $tokens = $client->getAccessToken();
}
catch(Netatmo\Exceptions\NAClientException $ex)
{
    handleError("An error happened while trying to retrieve your tokens: " .$ex->getMessage()."\n", TRUE);
}

//Retrieve user's Weather Stations Information

try
{
    //retrieve all stations belonging to the user, and also his favorite ones
    $data = $client->getData(NULL, TRUE);
    // Message affiché par le script Netatmo mais inutile dans notre utilisation
    //printMessageWithBorder("Informations Basiques de la Station Météo");
}
catch(Netatmo\Exceptions\NAClientException $ex)
{
    handleError("An error occured while retrieving data: ". $ex->getMessage()."\n", TRUE);
}

if(empty($data['devices']))
{
    echo 'No devices affiliated to user';
}
else
{

//------------------------------------------------------
// Ce qui suit est présent dans le script de Netatmo, mais n'est pas utile pour nous.
// À voir si on garde ou on supprime
//
//    $users = array();
//    $friends = array();
//    $fav = array();
//    $device = $data['devices'][0];
//    $tz = isset($device['place']['timezone']) ? $device['place']['timezone'] : "GMT";

    //devices are already sorted in the following way: first weather stations owned by user, then "friend" WS, and finally favorites stations. Still let's store them in different arrays according to their type
//     foreach($data['devices'] as $device)
//     {
// 
//         //favorites have both "favorite" and "read_only" flag set to true, whereas friends only have read_only
//         if(isset($device['favorite']) && $device['favorite'])
//             $fav[] = $device;
//         else if(isset($device['read_only']) && $device['read_only'])
//             $friends[] = $device;
//         else $users[] = $device;
//     }
//------------------------------------------------------

	// ------------------------------------------------
	// Ce qui suit provient du script Netatmo et sert à afficher les données récupérées.
	// Cela peut servir pour debugger.
	//
	//	$data = $client->getData(NULL, TRUE);
	//	foreach($data['devices'] as $device)
	//	{
	//    	echo $device['station_name'] . "\n";
	//    	print_r2($device['dashboard_data']);
	//    	foreach($device['modules'] as $module)
	//    	{
	//        	echo $module['module_name'];
	//        	print_r2($module['dashboard_data']);
	//        	echo '<br>';
	//    	}
	//    	echo '<br>';
	//	}
	// ------------------------------------------------
		
	// Je n'arrive pas à déterminer si ces deux lignes suivantes sont nécessaires ou pas...
	//$data = $client->getData('YOUR_DEVICE_ID');
	//$data = $client->getData('YOUR_FAV_DEVICE_ID', TRUE);
	
	// Pour Débug
	// print_r2($data);

	
	// *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
	// ================================= DONNÉES DES MESURES EN TEMPS REEL ================================= 
	// On écrit sur une ligne les différentes données extraites que l'on utilisera avec l'Arduino
	//
	// Je n'ai pas de pluviomètre, donc je commente ces lignes vu qu'elles ne retournent aucune infos
	// Mais du coup, ça décale les modules dans le tableau, ainsi le 1er module est le module extérieur
	// et le second module est le module chambre. Donc :
	// ["modules"][0] correspond à mon module extérieur
	// ["modules"][1] correspond à mon module intérieur Chambre
	// Il faudra donc déterminer les indices de vos modules et adapter le script en fonction
	//
	// *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
	//
	// MODULE EXTERIEUR //
	echo ("#EXT#");
	echo $data["devices"][0]["modules"][0]["dashboard_data"]["Temperature"]; 		//temp ext
	echo ("#");
	echo $data["devices"][0]["modules"][0]["dashboard_data"]["temp_trend"]; 		//temp ext trend
	echo ("#");
	echo $data["devices"][0]["modules"][0]["dashboard_data"]["Humidity"]; 			//Humidity

	// MODULE INTERIEUR PRINCIPAL - SALON //
	echo ("#SALON#");
	echo $data["devices"][0]["dashboard_data"]["Noise"];		 					//bruit
	echo ("#");
	echo $data["devices"][0]["dashboard_data"]["Temperature"]; 						//temp
	echo ("#");
	echo $data["devices"][0]["dashboard_data"]["temp_trend"]; 						//temp trend
	echo ("#");
	echo $data["devices"][0]["dashboard_data"]["Humidity"]; 						//humidity
	echo ("#");
	echo $data["devices"][0]["dashboard_data"]["Pressure"]; 						//pressure 
	echo ("#");
	echo $data["devices"][0]["dashboard_data"]["pressure_trend"]; 					//pressure trend
	echo ("#");
	echo $data["devices"][0]["dashboard_data"]["CO2"]; 								//CO2

	// MODULE INTERIEUR SECONDAIRE - CHAMBRE //
	echo ("#CHAMBRE#");
	echo $data["devices"][0]["modules"][1]["dashboard_data"]["Temperature"]; 		//temp
	echo ("#");
	echo $data["devices"][0]["modules"][1]["dashboard_data"]["temp_trend"]; 		//temp trend
	echo ("#");
	echo $data["devices"][0]["modules"][1]["dashboard_data"]["Humidity"]; 			//humidity
	echo ("#");
	echo $data["devices"][0]["modules"][1]["dashboard_data"]["CO2"]; 				//CO2
	echo ("#");

	// PLUVIOMETRE //      <--- Si j'en ajoutais un, il prendrait probablement l'indice ["modules"][2]
	//echo ("#PLUVIO#");
	//echo $data["devices"][0]["modules"][2]["dashboard_data"]["Rain"]; 			//pluie
	//echo ("#");
	//echo $data["devices"][0]["modules"][2]["dashboard_data"]["sum_rain_24"]; 		//pluie 24 h
	//echo ("#");
	//echo $data["devices"][0]["modules"][2]["dashboard_data"]["sum_rain_1"]; 		//pluie 1 h

	// Note pour une amélioration possible du script :
	// Il pourrait être intéressant d'utiliser la boucle foreach
	// pour les deux modules, mais pas sur que l'on gagne vraiment en code avec...

	// *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
	// =============================== FIN DU BLOC DES MESURES EN TEMPS REEL  ==============================
	// *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*



	// *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
	// ============================ RÉCUPÉRATION DE L'HISTORIQUE DES PRESSIONS  ============================
	// On récupère l'historique des pressions sur les 6 précédents jours
	// On devrait avoir 1 MESURE / 3 heures, donc sur 6 jours => 48 mesures
	//
	// *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*

	$device = $data['devices'][0];
	$module_id = NULL;	// Pour la pression, l'ID du module et du device sont les mêmes
	$scale = "3hours";				// Pour avoir une mesure toutes les heures
	$type = 'Pressure';
	$date_begin = time() -24*3600*6; // 6 jours
	$date_end = time(); //now
	$optimized = FALSE;
	$real_time = FALSE;
	
	try
    {
    	/* ---------------------- Les différents paramètres de la fonction getMeasure --------------------
		* @type PUBLIC, PRIVATE & PARTNER API
		* @param string $device_id
		* @param string $module_id (optional) if specified will retrieve the module's measurements, else it will retrieve the main device's measurements
		* @param string $scale : interval of time between two measurements. Allowed values : max, 30min, 1hour, 3hours, 1day, 1week, 1month
		* @param string $type : type of measurements you wanna retrieve. Ex : "Temperature, CO2, Humidity".
		* @param timestamp (utc) $start (optional) : starting timestamp of requested measurements
		* @param timestamp (utc) $end (optional) : ending timestamp of requested measurements.
		* @param int $limit (optional) : limits numbers of measurements returned (default & max : 1024)
		* @param bool $optimize (optional) : optimize the bandwith usage if true. Optimize = FALSE enables an easier result parsing
		* @param bool $realtime (optional) : Remove time offset (+scale/2) for scale bigger than max
		* @return array of measures and timestamp
		* @brief Method used to retrieve specifig measures of the given weather station
		*/
        $measurements = $client->getMeasure($device['_id'], $module_id, $scale, $type, $date_begin, $date_end, 1024, $optimized, $real_time);
        // La commande suivante sert à afficher les valeurs récupérées avec la commande précédentes.
        // Mais comme on veut les afficher avec un certains formattage...
        //printMeasure($measurements, $type, $tz, $device['_id'] ."'s 3 mesures par heures sur les 6 derniers jours");
    }
    catch(Netatmo\Exceptions\NAClientException $ex)
    {
        handleError("An error occured while retrieving main device's measurements over 6 days: " . $ex->getMessage() . "\n");
    }

	// On affiche les 48 dernières valeurs de pression (1 mesure / 3 heures, sur 6 jours => 48 mesures)
	$keys = explode(",", $type);

	// *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
	// Pour Debug des données récupérées
	if($debug == TRUE)
	{
		$compteur_val = 1;
		$compteur_mes = 1;
		$dix_valeurs_pression = "%";	// Pour récupérer seulement 10 valeurs en vue de créer/vérifier le programme Arduino
	}
	// Fin de la partie Debug
	// *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*

	echo '<br>';	// Un petit retour à la ligne pour séparer les nouvelles valeurs récupérées des précédentes 
	
	foreach($measurements as $timestamp => $values)
        {
            // echo $timestamp;
            // echo "<br>";
            foreach($values as $key => $val)
            { 
                // Pour chaque valeurs de mesures, on affiche cette valeur séparée de la précédente par un %
                //echo $keys[$key] . ": ";
               
                echo ("%");
                echo $val;
                
                // printUnit($keys[$key]);
                // if(count($values)-1 === $key || $monthly)
                //    echo "<br>";
                // else echo ", ";
				
				
				// *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
				// Pour Debug des données récupérées
				if($debug == TRUE)
				{
					// On met la valeur dans la variable $dix_valeurs avec le %
					if ($compteur_val < 11)		// tant que l'on n'a pas atteint les 10 valeurs
					{
						$dix_valeurs_pression = $dix_valeurs_pression . "$val%";
					}
					$compteur_val = $compteur_val + 1; // Je compte combien de valeurs sont présentes
				}
				// Fin de la partie Debug
				// *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
                

            }        
            	// *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
				// Pour Debug des données récupérées
				if($debug == TRUE)
				{
					$compteur_mes = $compteur_mes + 1; // Je compte combien de mesures sont présentes
				}
				// Fin de la partie Debug
				// *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
        }

	echo ("%");	// On marque la fin des mesures

	// *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
	// ============================ FIN DU BLOC DE L'HISTORIQUE DES PRESSIONS  =============================
	// *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*


	// *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
	// ========================= RÉCUPÉRATION DE L'HISTORIQUE DES TEMPÉRATURES MAX  ========================
	// On récupère l'historique des températures sur les 6 précédents jours
	// On devrait avoir 1 MESURE / 3 heures, donc sur 6 jours => 48 mesures
	//
	// *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*

	$device = $data['devices'][0];
	$module_id = $data['devices'][0]['modules'][0];	// Pour la temp. MAX, c'est sur le module extérieur qu'il faut prendre les données.
	$scale = "3hours";				// Pour avoir une mesure toutes les 3 heures
	$type = 'max_temp';
	$date_begin = time() -24*3600*6; // 6 jours
	$date_end = time(); //now
	$optimized = FALSE;
	$real_time = FALSE;
	
	try
    {
        $measurements = $client->getMeasure($device['_id'], $module_id['_id'], $scale, $type, $date_begin, $date_end, 1024, $optimized, $real_time);
        // La commande suivante sert à afficher les valeurs récupérées avec la commande précédentes.
        // Mais comme on veut les afficher avec un certains formattage...
        //printMeasure($measurements, $type, $tz, $device['_id'] ."'s 3 mesures par heures sur les 6 derniers jours");
    }
    catch(Netatmo\Exceptions\NAClientException $ex)
    {
        handleError("An error occured while retrieving main device's daily measurements: " . $ex->getMessage() . "\n");
    }

	// On affiche les 48 dernières valeurs de pression (1 mesure / 3 heures, sur 6 jours => 48 mesures)
	$keys = explode(",", $type);

	// *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
	// Pour Debug des données récupérées
	if($debug == TRUE)
	{
		$compteur_val = 1;
		$compteur_mes = 1;
		$dix_valeurs_temp_max = "%"; // Pour récupérer seulement 10 valeurs en vue de créer/vérifier le programme Arduino
	}
	// Fin de la partie Debug
	// *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*

	
	echo '<br>';	// Un petit retour à la ligne pour séparer les nouvelles valeurs récupérées des précédentes 
	
	foreach($measurements as $timestamp => $values)
        {
            // echo $timestamp;
            // echo "<br>";
            foreach($values as $key => $val)
            { 
                // Pour chaque valeurs de mesures, on affiche cette valeur séparée de la précédente par un %
                //echo $keys[$key] . ": ";
               
                echo ("%");
                echo $val;
                
                // printUnit($keys[$key]);
                // if(count($values)-1 === $key || $monthly)
                //    echo "<br>";
                // else echo ", ";
				
				
				// *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
				// Pour Debug des données récupérées
				if($debug == TRUE)
				{
					// On met la valeur dans la variable $dix_valeurs avec le %
					if ($compteur_val < 11)		// tant que l'on n'a pas atteint les 10 valeurs
					{
						$dix_valeurs_temp_max = $dix_valeurs_temp_max . "$val%";
					}
					$compteur_val = $compteur_val + 1; // Je compte combien de valeurs sont présentes
				}
				// Fin de la partie Debug
				// *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
                

            }        
            	// *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
				// Pour Debug des données récupérées
				if($debug == TRUE)
				{
					$compteur_mes = $compteur_mes + 1; // Je compte combien de mesures sont présentes
				}
				// Fin de la partie Debug
				// *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
        }
	
	echo ("%");	// On marque la fin des mesures
	
	// *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
	// ========================= FIN DU BLOC DE L'HISTORIQUE DES TEMPÉRATURES MAX  =========================
	// *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*

	
	// *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
	// ========================= RÉCUPÉRATION DE L'HISTORIQUE DES TEMPÉRATURES MIN  ========================
	// On récupère l'historique des températures sur les 6 précédents jours
	// On devrait avoir 1 MESURE / 3 heures, donc sur 6 jours => 48 mesures
	//
	// *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*

	$device = $data['devices'][0];
	$module_id = $data['devices'][0]['modules'][0];	// Pour la temp. MIN, c'est sur le module extérieur qu'il faut prendre les données.
	$scale = "3hours";				// Pour avoir une mesure toutes les 3 heures
	$type = 'min_temp';
	$date_begin = time() -24*3600*6; // 6 jours
	$date_end = time(); //now
	$optimized = FALSE;
	$real_time = FALSE;
	
	try
    {
        $measurements = $client->getMeasure($device['_id'], $module_id['_id'], $scale, $type, $date_begin, $date_end, 1024, $optimized, $real_time);
        // La commande suivante sert à afficher les valeurs récupérées avec la commande précédentes.
        // Mais comme on veut les afficher avec un certains formattage...
        //printMeasure($measurements, $type, $tz, $device['_id'] ."'s 3 mesures par heures sur les 6 derniers jours");
    }
    catch(Netatmo\Exceptions\NAClientException $ex)
    {
        handleError("An error occured while retrieving main device's daily measurements: " . $ex->getMessage() . "\n");
    }

	// On affiche les 48 dernières valeurs de Temp MIN (1 mesure / 3 heures, sur 6 jours => 48 mesures)
	$keys = explode(",", $type);

	// *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
	// Pour Debug des données récupérées
	if($debug == TRUE)
	{
		$compteur_val = 1;
		$compteur_mes = 1;
		$dix_valeurs_temp_min = "%"; // Pour récupérer seulement 10 valeurs en vue de créer/vérifier le programme Arduino
	}
	// Fin de la partie Debug
	// *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
	
	echo '<br>';	// Un petit retour à la ligne pour séparer les nouvelles valeurs récupérées des précédentes 
	
	foreach($measurements as $timestamp => $values)
        {
            // echo $timestamp . '=> ' . $values;
			// echo "<br>";
            foreach($values as $key => $val)
            { 
                // Pour chaque valeurs de mesures, on affiche cette valeur séparée de la précédente par un %
                //echo $keys[$key] . ": ";
               
                echo ("%");
                echo $val;
                
                // printUnit($keys[$key]);
                // if(count($values)-1 === $key || $monthly)
                //    echo "<br>";
                // else echo ", ";
                
				// *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
				// Pour Debug des données récupérées
				if($debug == TRUE)
				{
					// On met la valeur dans la variable $dix_valeurs avec le %
					if ($compteur_val < 11)		// tant que l'on n'a pas atteint les 10 valeurs
					{
						$dix_valeurs_temp_min = $dix_valeurs_temp_min . "$val%";
					}
					$compteur_val = $compteur_val + 1; // Je compte combien de valeurs sont présentes
				}
				// Fin de la partie Debug
				// *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
                

            }        
            	// *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
				// Pour Debug des données récupérées
				if($debug == TRUE)
				{
					$compteur_mes = $compteur_mes + 1; // Je compte combien de mesures sont présentes
				}
				// Fin de la partie Debug
				// *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
        }
	
	echo ("%");	// On marque la fin des mesures


	// *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
	// Pour Debug des données récupérées
	if($debug == TRUE)
	{
		echo "<br><br>Échantillon de 10 valeurs de pression :<br>";
		echo $dix_valeurs_pression; // On affiche la variable contenant les 10 valeurs de chaque 
		echo "<br><br>Échantillon de 10 valeurs de températures maximales :<br>";
		echo $dix_valeurs_temp_max; // On affiche la variable contenant les 10 valeurs de chaque 
		echo "<br><br>Échantillon de 10 valeurs de températures minimales :<br>";
		echo $dix_valeurs_temp_min; // On affiche la variable contenant les 10 valeurs de chaque 
	}
	// Fin de la partie Debug
	// *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*



	// *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
	// ========================= FIN DU BLOC DE L'HISTORIQUE DES TEMPÉRATURES MIN  =========================
	// *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
	
	
	// C'est la fin du script qui récupère les données de notre station météo //
	
	
	// *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
	// =========================                                                   =========================	
	// Ce qui suit est inutile pour notre utilisation, mais peut servir en cas de debuggage
	// Par exemple lors de l'ajout d'un module, c'est pourquoi je laisse ce code en commentaire
	/*
    //print first User's device Then friends, then favorite
    printDevices($users, "User's weather stations");
    
    //printDevices($friends, "User's friends weather stations");
    //printDevices($fav, "User's favorite weather stations");

    // now get some daily measurements for the last 30 days
    $type = "temperature,Co2,humidity,noise,pressure";

    //first for the main device
    try
    {
        $measure = $client->getMeasure($device['_id'], NULL, "1day" , $type, time() - 24*3600*30, time(), 30,  FALSE, FALSE);
        printMeasure($measure, $type, $tz, $device['_id'] ."'s daily measurements of the last 30 days");
    }
    catch(Netatmo\Exceptions\NAClientException $ex)
    {
        handleError("An error occured while retrieving main device's daily measurements: " . $ex->getMessage() . "\n");
    }


    //Then for its modules
    foreach($device['modules'] as $module)
    {
        //requested data type depends on the module's type
        switch($module['type'])
        {
            case "NAModule3": $type = "sum_rain";
                              break;
            case "NAModule2": $type = "WindStrength,WindAngle,GustStrength,GustAngle,date_max_gust";
                              break;
            case "NAModule1" : $type = "temperature,humidity";
                               break;
            default : $type = "temperature,Co2,humidity";
        }
        try
        {
            $measure = $client->getMeasure($device['_id'], $module['_id'], "1day" , $type, time()-24*3600*30 , time(), 30,  FALSE, FALSE);
            printMeasure($measure, $type, $tz, $module['_id']. "'s daily measurements of the last 30 days ");
        }
        catch(Netatmo\Exceptions\NAClientException $ex)
        {
            handleError("An error occured while retrieving main device's daily measurements: " . $ex->getMessage() . "\n");
        }

    }

    //Finally, retrieve general info about last month for main device
    $type = "max_temp,date_max_temp,min_temp,date_min_temp,max_hum,date_max_hum,min_hum,date_min_hum,max_pressure,date_max_pressure,min_pressure,date_min_pressure,max_noise,date_max_noise,min_noise,date_min_noise,max_co2,date_max_co2,min_co2,date_min_co2";
    try
    {
        $measures = $client->getMeasure($device['_id'], NULL, "1month", $type, NULL, "last", 1, FALSE, FALSE);
        printMeasure($measures, $type, $tz, "Last month information of " .$device['_id'], TRUE);
    }
    catch(Netatmo\Exceptions\NAClientException $ex)
    {
        handleError("An error occcured while retrieving last month info: ".$ex->getMessage() . " \n");
    }
	// =========================                                                   =========================	
	// *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
    */
}
?>

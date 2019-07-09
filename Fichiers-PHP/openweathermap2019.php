<?php

// Pour récupérer les données publique de température de la ville où vous habitez, il faut
// avoir créé un compte en suivant la procédure décrite ici : https://openweathermap.org/appid
// L'appel à l'API se fait avec le lien :
//         http://api.openweathermap.org/data/2.5/forecast?id=524901&APPID={APIKEY}
// La clé de l'API est stocké dans le fichier config-OMW.php.

// *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
// ON vérifie ici si l'extention OpenSSL est bien activée dans le serveur,
// sinon la récupération via HTTPS ne fonctionnera pas ! Il faudrait alors utiliser HTTP...
// Ce qui est moins sécurisé.
// Les lignes suivantes permettent de vérifier que tout est OK :
//
//		$w = stream_get_wrappers();
//		echo 'openssl: ',  extension_loaded  ('openssl') ? 'yes':'no', "<br>";
//		echo 'http wrapper: ', in_array('http', $w) ? 'yes':'no', "<br>";
//		echo 'https wrapper: ', in_array('https', $w) ? 'yes':'no', "<br>";
//		echo 'wrappers: ', var_export($w);
//
// Mais les deux tests ci-dessous permettent d'arrêter le script si jamais le SSL et HTTPS wrapper sont FALSE
if (!extension_loaded  ('openssl'))
{
	echo 'Ce script de récupération de données météo sur OpenWeatherMap via leur API nécessite l\'extension OpenSSL sur le serveur.';
	throw new Exception('Ce script de récupération de données météo sur OpenWeatherMap via leur API nécessite l\'extension OpenSSL sur le serveur.');
}

if (!in_array('https', stream_get_wrappers()))
{
	echo 'Ce script de récupération de données météo sur OpenWeatherMap via leur API nécessite l\'extension OpenSSL sur le serveur ET que https wrapper soit actif.';
	throw new Exception('Ce script de récupération de données météo sur OpenWeatherMap via leur API nécessite l\'extension OpenSSL sur le serveur ET que https wrapper soit actif.');
}
// *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*

// *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
// *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*      DEBUG      *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
$debug = FALSE;
$debug2 = FALSE;


// Petite fonction pour afficher avec des retours les tableaux lors d'un debug
function print_r2($val){
        echo '<pre>';
        print_r($val);
        echo  '</pre>';
}
// *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*    FIN DEBUG    *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*


// *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
// On défini ici la variable du chemi absolu de là où se trouve le script php
// Sur mon synology, la fonction dirname(dirname(__FILE__)) donnait que /VolumeX
// alors que le fichier php était dans /VolumeX/web/ , donc j'ajoute /web/ après le résultat de dirname(dirname(__FILE__))
define('__ROOT__', dirname(dirname(__FILE__)) . '/web/');

// On définit ici la variable de chemin d'accès au fichier nécessaire à inclure
// Il faudra avoir placé le fichier dans le dossier src (fourni par Netatmo, même si ici on n'utilse plus les API Netatmo
define('_configpath_', __ROOT__ . 'src/Config-OWM.php');

// On inclue (PHP vérifie si le fichier a déjà été inclus, et si c'est le cas, ne l'inclut
// pas une deuxième fois) et exécute le fichier précédent.
// Et avec require_once lorsqu'une erreur // survient, le script est arrêté, et plus rien
// ne se passe ensuite. 

require_once (_configpath_);
// *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*


// On défini ici le code de la ville pour laquelle les données de prévisions vont être récupérées
// Pour récupérer le code de la ville, il faut aller ici : https://openweathermap.org/city
// Puis chercher la ville en question, et récupérer le n° qui sera présent dans l'URL.
// Par exemple, Paris a pour code 2988507.
//
$city_code = '2988507';

// On crée l'url qui va servir à appeler l'API puis à récupérer les données
$url = "https://api.openweathermap.org/data/2.5/forecast?id=$city_code&APPID=$omw_api_key&units=metric&lang=fr";

$request = file_get_contents($url);

$json_weather_data = json_decode($request,true);

// *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
// Pour Debug des données récupérées
if($debug == TRUE)
{
	echo '<br>DEBUG<br>';
	print_r2($url);
	echo '<br>DEBUG<br>';
	print_r2($json_weather_data["list"]);
	//var_dump ($json_weather_data);	// Pour du débuggage
	echo '<br>DEBUG<br>';
}
if($debug2 == TRUE)
{
	$compteur_val = 1;		// Pour compter le nombre de valeurs obtenues
	$dix_valeurs = "#";		// Variable qui va stocker les 10 séries de mesures
}
// Fin de la partie Debug
// *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*

echo ("#");

foreach($json_weather_data["list"] as $index => $list)		// Il devrait y avoir 40 valeurs car 5 jours
{															// avec 1 mesures toutes les 3 h
	echo $list["dt"]; 					// Time of data forecasted, unix, UTC
	echo ("#");
	echo $list["main"]["temp"]; 		// Temperature. Unit Default: Kelvin, Metric: Celsius, Imperial: Fahrenheit.
	echo ("#");
	echo $list["weather"][0]["icon"]; 	// Weather icon id (météo)
	echo ("#");
	echo $list["clouds"]["all"]; 		// Nuageux en %
	echo ("#");
	
	// Attention, il arrive qu'il n'y ait aucune donnée sur la pluie... donc rien n'est écrit à ce niveau là !
	// Il faudra vérifier si ça ne provoque pas des erreurs dans le script de l'Arduino...
	// On va faire un test si la valeut du volume de pluie est non existant, alors on remplace par 0
	if ($list["rain"]["3h"] == NULL)	// Rain volume for last 3 hours, mm
	{
		echo '0'; 					// Si la quantité n'est pas présent, on écrit 0.
	}
	else
	{
		echo $list["rain"]["3h"];	// Si la quantité est présente, on l'écrit
	}
	echo ("#");
	// On peut aussi récupérer les infos sur le vent, on verra si on l'utilise avec un écran un peu plus grand...
	//echo $json_weather_data["list"][$i]["wind"]["speed"]; // Wind speed. Unit Default: meter/sec, Metric: meter/sec, 
	//echo ("#");


		// *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
	// Pour Debug des données récupérées - On va récupérer 10 valeurs pour créer/tester le prorgamme Arduino
	if($debug2 == TRUE)
	{
		if ($compteur_val < 11)		// tant que l'on n'a pas atteint les 10 valeurs
		{
			$dix_valeurs = $dix_valeurs . $list["dt"] . "#" . $list["main"]["temp"] . "#" . $list["weather"][0]["icon"] . "#" . $list["clouds"]["all"] . "#";
			if ($list["rain"]["3h"] == NULL)	// Rain volume for last 3 hours, mm
			{
				$dix_valeurs = $dix_valeurs . '0#'; 	// Si la quantité n'est pas présent, on écrit 0.
			}
			else
			{
				$dix_valeurs = $dix_valeurs . $list["rain"]["3h"] . "#";	// Si la quantité est présente, on l'écrit
			}
		}
		$compteur_val = $compteur_val + 1;
	}
	// Fin de la partie Debug
	// *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*

	
}

// *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*
// Pour Debug des données récupérées
if($debug2 == TRUE)
{
	echo "<br><br>Échantillon de 10 lots de valeurs de prévisions météo :<br>";
	echo $dix_valeurs; // On affiche la variable contenant les 10 lots de valeurs
}
// Fin de la partie Debug
// *-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*

?>
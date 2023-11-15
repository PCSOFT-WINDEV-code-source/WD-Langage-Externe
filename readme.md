  
<span style="font-family:Arial sans-serif;font-size:16px;">WD Langage Externe</span>

  
<span style="font-family:Arial sans-serif;font-size:14px;">WD Langage Externe</span>

  
<span style="font-family:Arial sans-serif;font-size:14px;">Cet exemple illustre l'utilisation de fenêtres faites avec WINDEV dans une application en C++ (Visual Studio 2005) et MFC.</span>

<span style="font-family:Arial sans-serif;font-size:14px;">Dans cet exemple, nous abordons deux façon d'appeler du WLangage:</span>

<span style="font-family:Arial sans-serif;font-size:14px;">1/ Avec la fonction nWDExecute</span>

<span style="font-family:Arial sans-serif;font-size:14px;">2/ Avec les appels à des procédures simples livrées dans WDExternApi.h</span>

  
<span style="font-family:Arial sans-serif;font-size:14px;">C'est le Langage externe qui appelle WINDEV, et donc la démarche consiste à exécuter un programme en langage externe (ici en C++ - Visual Studio 2005) utilisant des ressources développées avec WINDEV (ici une bibliothèque).</span>

  
<span style="font-family:Arial sans-serif;font-size:14px;">Résumé de l'exemple livré avec WINDEV : </span>

<span style="font-family:Arial sans-serif;font-size:14px;">L'exemple est celui d'une gestion de réservation dans un camping. Les fenêtres de l'interface Homme machine sont faites avec WINDEV et elles font appel à du code C++ à l'aide de "WDTouche". Le code C++ contient quant à lui des appels à du code WLangage pour récupérer les valeurs des champs, afficher des valeurs dans des champs et exécuter directement des fonctions en WLangage. </span>

  
  
<span style="font-family:Arial sans-serif;font-size:14px;">( \_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_ ° \_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_\_ )</span>

  
<span style="font-family:Arial sans-serif;font-size:10px;">Conditions d'utilisation :</span>

<span style="font-family:Arial sans-serif;font-size:10px;">Le programme est fourni dans un but didactique.</span>

<span style="font-family:Arial sans-serif;font-size:10px;">L'utilisation de ce programme s'effectue sous la responsabilité de son utilisateur. La responsabilité de PC SOFT ne pourra en aucun cas être mise en cause si le programme ne fonctionne pas tel que vous l'attendez, ou pour quelque raison que ce soit. </span>

<span style="font-family:Arial sans-serif;font-size:10px;">Tout détenteur d'une licence WINDEV 28 enregistrée est autorisé à modifier ce programme, et est autorisé à l'inclure dans une ou plusieurs de ses applications. Dans ces cas, toute mention se rapportant à PC SOFT, à WinDev ou à WebDev devra être supprimée, afin qu'aucun doute ne puisse subsister dans l'esprit d'un utilisateur final.</span>

<span style="font-family:Arial sans-serif;font-size:10px;">Il est interdit de diffuser ou vendre ce programme exemple sans modification substantielle, ou sans l'inclure dans une application de taille substantielle.</span>

<span style="font-family:Arial sans-serif;font-size:10px;">Le support technique pour ce programme exemple est accessible à travers le service "Assistance Directe" uniquement.</span>

<span style="font-family:Arial sans-serif;font-size:10px;">Attention: si plusieurs personnes sont susceptibles d'avoir consulté ce programme, il se peut que le programme ait été modifié! </span>

<span style="font-family:Arial sans-serif;font-size:10px;">Assurez-vous d'étudier une version originale de ce programme.</span>

  
  
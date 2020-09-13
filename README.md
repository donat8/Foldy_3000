# Foldy_3000
MFC application for easier searching and organising of folders and files 
-------------------------------------------------------------------------------------------------
* Aplikaciju je moguće pokrenuti, pomoću .exe filea.
* Builda se bez problema u 32/64 bitnoj i debug/release verziji

-------------------------------------

<h3>Uputstva za korištenje aplikacije:</h3>

* S lijeve strane se nalazi Shell Tree view kontrola popunjena svim mapama koje se nalaze na računalu koje upravo koristimo, ta kontrola nam omogućuje 
  da odjednom označimo više mapa, 

  <p align="center">
  <img src="https://www.linkpicture.com/q/1_295.jpg" />
  </p>

 također, ako pritisnemo na određeni folder možemo ga vidjeti u Shell List viewu. Mape koje imaju podmape moguće je otvoriti i zatvoriti pomoću + i -
  
  <p align="center">
  <img src="https://www.linkpicture.com/q/2_106.png" />
  </p>
 
 
 
* S desne gornje strane nalazi se Shell List view kontrola koji sadrži sve datoteke i mape od mape koje smo pritisnuli u Shell Tree viewu 
  (potrebno je obratiti pozornost na to da nije isto, kada se mapa označi sa kvačicom, i kada se pritisne folder), te ona služi kako bismo   
  mogli s lakoćom pogledati što se u određenoj mapi nalazi
  
  <p align="center">
  <img src="https://www.linkpicture.com/q/3_84.png" />
  </p>
  
  ----------------------------------------------------------------------------------------------------------
  
* U doljnjem desnom dijelu je dio gdje unosimo jednu ključnu riječ(keyword) koju želimo pretraživati (oprez! Velika i mala slova su bitna!)
  Također pretraga po ekstenziji je isto moguća.
  
    <p align="center">
  <img src="https://www.linkpicture.com/q/4_63.png" />
  </p>

* Ispod nje se nalazi Browse kontrola (To where?) koja nam omogućuje da nam se pritiskom na gumb otvara dijalog u kojem možemo birati mapu u koju želimo spremiti
  sve rezultate pretrage.
  
     <p align="center">
  <img src="https://www.linkpicture.com/q/5_48.png" />
  </p>

* Zadnji je gumb Copy them! koji kopira sve datoteke i mape koje sadrže ključnu riječ iz mapa koje smo označili kvačicom u Shell Tree viewu, 
  u mapu koja je prije odabrana u Browse kontroli.
  
  <p align="center">
  <img src="https://www.linkpicture.com/q/6_48.png" />
  </p>
  
* Gumb neće imati svoju funkciju sve dok se ne obave sve potrebne stvari, svaka kontrola ima svoje upozorenje, te će upozoriti korisnika ako je zaboravio
  unjeti npr. ključnu riječ
  
 * Ako je pri pritisku gumba "Copy them!", kopiranje uspješno, pored gumba Copy se pojavi tekst "Success!", ako ne, ispiše se "Copying failed".
 

  <p align="center">
  <img src="https://www.linkpicture.com/q/8_37.png" />
  </p>
  
  <p align="center">
  <img src="https://www.linkpicture.com/q/7_40.png" />
  </p>

  ---------------------------------------------
  
  Primjer:
  
 * U Shell view kontroli možemo vidjeti da imamo prazan folder "Munchkin", u folderu "Mice".
  Taj folder ćemo upotrijebiti kao mjesto gdje se spremaju rezultati pretrage, tako da stisnemo gumb foldera sa povećalom i odaberemo ga iz dijaloga.
  

  <p align="center">
  <img src="https://www.linkpicture.com/q/9_36.png" />
  </p>
  
*  Ako pritisnemo folder "Mice", možemo vidjeti da se u njemu nalaze različite slike mačaka, različitih vrsta, mi želimo u naš folder "Munchkin" kopirati
  samo one slike koje u imenu imaju ključnu riječ "munchkin".
  Označavamo kvačicom folder iz kojega želimo kopirati ("Mice") i unosimo ključnu riječ "munchkin".
  Pritisne se gumb "Copy them" za kopiranje.
   <p align="center">
  <img src="https://www.linkpicture.com/q/11_30.png" />
  </p>
  
*  Kopiranje je uspješno jer pored gumba "Copy them!" piše "SUCCESS", pritiskom na folder "Munchkin" možemo vidjeti da su se sve datoteke koje sadržavaju ključnu riječ
  kopirale u naš željeni folder.
  
 <p align="center">
  <img src="https://www.linkpicture.com/q/12_34.png" />
  </p>
  
  I to je to.
  
  
  

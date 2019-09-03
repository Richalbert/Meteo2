import QtQuick 2.0
import QtQuick.Window 2.0

Window
{
    	visible: true
    	width: 600
    	height: 600
    	title: "Meteo & Tendance"

    
    	function update() {
        	mesure.refresh()
        
        	var t = "<h2>%1 °C</h2>"
        	idTemperature.text = t.arg(mesure.temp)
        
        	/* test * /
        	if (mesure.temp > 30.5) {
            		idTendance.source = "icones/fleche_haut.svg"
        	} else {
            		idTendance.source = "icones/fleche_bas.svg"
       	 	}
       	 	*/
       	 	
       	 	//TODO : nous sommes en ete
			//console.log (" a =", mesure.pente)

			//idTendance.rotation = -1 * Math.atan(mesure.pente * 10110) * 180/Math.PI
			idTendance.rotation = -1 * mesure.pente

//			if (mesure.pente > 0.00006567) {
//				idTendance.source = "icones/fleche_haut.svg"
//			} else {
//				if (mesure.pente <-0.00006567) {
//					idTendance.source = "icones/fleche_bas.svg"
//				} else {
//					idTendance.source = "icones/fleche_egal.svg"
//				}
//			}
			
			
			
			
			
        
        	var p = "<h2>%1 hPa</h2>"
        	idPression.text = p.arg(mesure.pression/100)
        
        	var h = "<h2>%1 %</h2>"
        	idHumidite.text = h.arg(mesure.humidite)

	}

	function maFonction() {
        	var d = "<h2>%1 </h2>"
        	idDescription.text = d.arg(mesure.description)
		
		var icn = "icones/%1.svg"
		icone_img.source = icn.arg(mesure.icone)

	} 

   	Timer {
		interval: 2000
		repeat: true
		running: true
		triggeredOnStart: true
		onTriggered: update(), maFonction()
	}
	
	
    	Rectangle { 	//pression
        	x: 0 ; y: 0
        	width: parent.width/3
        	height: parent.height/3
        	//color: "cornflowerblue"
    		color: "burlywood"

       		Text {
            		color: "black"
            		text: "<b>Pression atmosphérique</b>"
        	}

        	Text {
            		id: idPression
            		color: "black"
            		anchors.centerIn: parent
         		text: "<h2>1024 hPa</h2>"
        	}    
    	}
    
    
    	Rectangle { 	//temperature
   		x: 0; y: parent.height/3
    		width: parent.width/3
    		height: parent.height/3
    		//color: "darkcyan"
        	color: "wheat"

    		Text {
         		color: "black"
         		text: "<b>Température</b>"
        	}
	    
    		Text {
         		id: idTemperature
         		color: "black"
         		anchors.centerIn: parent
         		text: "<h2>30°C</h2>"
        	}    

    		/*Image {
            		sourceSize.width: Math.min(8*(parent.width/10),8*(parent.height/10))
            		sourceSize.height: Math.min(8*(parent.width/10),8*(parent.height/10))
            		anchors.centerIn: parent.width
            		source: "thermometer.svg"
        	}*/
   	 }
    
    
    	Rectangle { 	//humidite
    		x: 0
    		y: 2*(parent.height/3)
    
    		width: parent.width/3
    		height: parent.height/3
    		//color: "cadetblue"
		color: "blanchedalmond"

    		Text {
         		color: "black"
         		text: "<b>Humidité</b>"
        	}

    		Text {
         		id: idHumidite
         		color: "black"
         		anchors.centerIn: parent
         		text: "<h2>30 %</h2>"
        	}    
    	}
        

    	Rectangle {	//icone
        	id:icone
        	x: parent.width/3
        	y: 0
        	width: 2*(parent.width/3)
        	height: 2*(parent.height/3)
        	//color: "lightblue"
		//color: "transparent"
		color: "blanchedalmond"

	        Image {
			id: icone_img
          	  	sourceSize.width: Math.min(parent.width,parent.height)
           	 	sourceSize.height: Math.min(parent.width,parent.height)
            		anchors.centerIn: parent
            	source: "icones/039-sun.svg"
        	}



			Text {
				id: idDate
				color: "black"
				text: "<b>Aujourd'hui : 2 mai 2019</b>"
			}

		}



    	Rectangle { 	//tendance
        	id: tendance
        	x:parent.width/3
        	y:2*(parent.height/3)
        	width: parent.width/3
        	height: parent.height/3
        	//color: "lightskyblue"
        	color: "wheat"
        
		Text {
            		color: "black"
            		text: "<b>Tendance</b>"
        	}

        	Image {
            		id: idTendance
            		sourceSize.width:  Math.min(parent.width,parent.height)
            		sourceSize.height: Math.min(parent.width,parent.height)
            		anchors.centerIn: parent
                    transformOrigin: Item.Center
                    rotation: 0
            		source: "icones/fleche_egal.svg"
        	}
    	}
    

	Rectangle { 	// description
        	x:2*(parent.width/3)
        	y:2*(parent.height/3)
        	width: parent.width/3
        	height: parent.height/3
        	//color: "paleturquoise"
        	color: "burlywood"
        	
        
		Text{
        		color: "black"
        		text: "<b>Description</b>"
        	}

        	Text {
			id: idDescription
        		color: "black"
        		anchors.centerIn: parent
        		text: "Il fait super beau !"
        	}
    	}


}


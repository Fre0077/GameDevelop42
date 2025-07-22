#ifndef INDEX_H
# define INDEX_H

# include "WorldGenerator.hpp"
# include "DataManager.hpp"
# include "Rendering.hpp"
# include "Texture.hpp"
# include "VertexCreator.hpp"

// WORLDGENERATOR: genera un chunck del mondo in base alla chimata. un qualsiasi blocco del chunck triggerà la sua creazione
// VERTEXCREATOR: salva sono i vertici che verrano rendirizzati (prima di texture)
// DATAMANAGER: gestisce salvataggio ed accesso hai dati del mondo ed il seed
// RENDERING: renderizza i dati che lgi vengono inviati (passaggio finale)
// TEXTURE: aggiunge ai vertici le informazioni U V per il posizionamento delle texture (prima di rendering)

#endif
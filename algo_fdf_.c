/* ************************************************************************** */
/*                                                                            */
/*                                                        :::      ::::::::   */
/*   algo_fdf_.c                                        :+:      :+:    :+:   */
/*                                                    +:+ +:+         +:+     */
/*   By: fjanoty <marvin@42.fr>                     +#+  +:+       +#+        */
/*                                                +#+#+#+#+#+   +#+           */
/*   Created: 2016/03/04 11:15:38 by fjanoty           #+#    #+#             */
/*   Updated: 2016/03/06 05:52:21 by fjanoty          ###   ########.fr       */
/*                                                                            */
/* ************************************************************************** */

-parser le fichier fdf
-les event/fenetre/mlx
-transformation des couleur tsl->rgb   &&   rgb->tsl


-effet
	-degrader (en fonction de des format de couleur)
	-brouillard de guerre
	-trajectoir de cam (si fichier cam)
		-pas a pas
		-increment de vitesse
		-orientation de cam

-obj:
	-cam
		-libre
			-rotation
			-translation
		-fichier trajectoire
	-scene
			-translation
			-rotation (changement de base)
			-projection isometrique

-impression ecran
					-ligne
					-triangle/rectangle (zbuffer ou pas)


format fichier:
	-point librement linker ou des .obj pck c rigolo
	-fichier animation

generateur de forme sur oint libre

affichage menu:
				-pos (cam)

-definir une couleur e fonction de z (de la scene)
-bloquer l;impression de pixel qui ne sont pas dans le champ
-finaliser l'implementaion des couleur
-implementer l'impression de quadrialetre

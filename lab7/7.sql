SELECT AVG(songs.energia) AS energia_media FROM songs JOIN artists ON songs.artist_id = artists.id WHERE artists.name = 'Drake';

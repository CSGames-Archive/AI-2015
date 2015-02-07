/* ------------------------------------------------------------------------------
 ** _________   _________      ________    _____      _____  ___________ _________
 ** \_   ___ \ /   _____/     /  _____/   /  _  \    /     \ \_   _____//   _____/
 ** /    \  \/ \_____  \     /   \  ___  /  /_\  \  /  \ /  \ |    __)_ \_____  \ 
 ** \     \____/        \    \    \_\  \/    |    \/    Y    \|        \/        \
 **  \______  /_______  /     \______  /\____|__  /\____|__  /_______  /_______  /
 **         \/        \/             \/         \/         \/        \/        \/ 
 **
 ** Mine.java
 ** A mine
 **
 ** Author: Samuel-Ricardo Carriere
 ** ------------------------------------------------------------------------------*/

package world;

public class Mine {

	private boolean isReady;

	public Mine() {
		this.isReady = true;
	}

	public boolean isReady() {
		return isReady;
	}
	
	public void drop() {
		isReady = false;
	}
	
	public void hit() {
		isReady = true;
	}	
}
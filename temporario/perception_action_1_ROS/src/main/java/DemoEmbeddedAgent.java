import embedded.mas.bridges.jacamo.EmbeddedAgent;
import embedded.mas.bridges.jacamo.DefaultDevice;
import embedded.mas.bridges.jacamo.DemoDevice;
import embedded.mas.bridges.ros.Ros4EmbeddedMas;

import jason.asSyntax.Atom;

public class DemoEmbeddedAgent extends EmbeddedAgent {

	@Override
	public void initAg() {
		super.initAg();
	}

	@Override
	protected void setupSensors() {

		Ros4EmbeddedMas arduino = new Ros4EmbeddedMas();
		// arduino.openConnection();

		DefaultDevice device = new MyDemoDevice(new Atom("arduino1"), arduino);
		this.addSensor(device);



	}

}
